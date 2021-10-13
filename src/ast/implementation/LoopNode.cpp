//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/LoopNode.h>
#include <ast/FunctionNode.h>
#include <ast/VariableDerefNode.h>
#include <ast/EmptyNode.h>

namespace flare::ast {

    extern Context *globalContext;
    extern Node *mLoopNode;
    extern std::vector<Node *> lopStatementLists;
    bool isCodegenThreadedLoopBody = false;


    Value *createCall(Context *cxt, std::string name, Type *returnType, ArrayRef<Type *> paramTypes,
                      ArrayRef<Value *> args, bool isVarArg) {
        auto *f = FunctionType::get(
                returnType,
                paramTypes,
                isVarArg
        );
        auto function = module->getOrInsertFunction(name, f);
        return cxt->getBuilder()->CreateCall(function, args);
    }

    LoopNode::LoopNode(Node *cond, Node *smt) {
        this->condition = cond;
        this->statementList = smt;

        this->analyzer = new LoopAnalyzer(smt);
    }

    llvm::Value *LoopNode::codeGen(Context *cxt) {

        globalContext = cxt;
        mLoopNode = this;
        lopStatementLists.clear();

        this->printCallStack(cxt, "LoopNode", __FUNCTION__);


        if (this->preLoop != nullptr) {
            this->preLoop->codeGen(cxt->nextLevel());
        }

        Function *insertFunction = builder.GetInsertBlock()->getParent();

        BasicBlock *conditionBlock = BasicBlock::Create(context, "loopCondition", insertFunction);
        BasicBlock *bodyBlock = BasicBlock::Create(context, "loopBody", insertFunction);
        BasicBlock *mergeBlock = BasicBlock::Create(context, "loopMerge", insertFunction);

        // TODO improve this implementation
        builder.CreateBr(conditionBlock);

        builder.SetInsertPoint(conditionBlock);
        builder.CreateCondBr(
                this->condition->codeGen(cxt->nextLevel()),
                bodyBlock,
                mergeBlock
        );

        builder.SetInsertPoint(bodyBlock);
        if (this->before != nullptr) {
            this->before->codeGen(cxt->nextLevel());
        }
        this->statementList->codeGen(cxt->nextLevel());
        if (this->after != nullptr) {
            this->after->codeGen(cxt->nextLevel());
        }
        if (builder.GetInsertBlock()->getTerminator() == nullptr) {
            builder.CreateBr(conditionBlock);
        }

        for (auto i: analyzer->getPrivatizationVars()) {
            auto x = dynamic_cast<VariableDerefNode *>(i);
            std::cout << x->variableName << "==\n\n";
            std::cout.flush();
        }

        if (analyzer->isParallizable()) {
            this->codeGenThreadedLoopBody(cxt);
        }

        builder.SetInsertPoint(mergeBlock);

        if (analyzer->isParallizable()) {
            this->codeGenCallThreadedLoopBody(cxt);
        }

        mLoopNode = nullptr;
        globalContext = nullptr;

        return nullptr;
    }

    NodeType LoopNode::getNodeType() {
        return LOOP_NODE;
    }

    llvm::Value *LoopNode::codeGenThreadedLoopBody(Context *cxt) {

        auto pVars = this->analyzer->getPrivatizationVars();

        std::vector<llvm::Type *> items;
        for (auto *ele: pVars) {
            auto x = dynamic_cast<VariableDerefNode *>(ele);
            VarDeclNode *vNode = globalContext->findVariable(x->variableName);
            items.push_back(vNode->getLLVMVarRef()->getType());
        }

        // Create LLVM type
        this->varPrivateType = StructType::create(context, items, "function_private_vars");

        this->varPassType = StructType::create(context,
                                               {builder.getInt64Ty(), PointerType::get(this->varPrivateType, 0)},
                                               "function_pass_type");

        auto type = FunctionType::get(
                cxt->getBuilder()->getVoidTy(),
                {PointerType::get(cxt->getBuilder()->getVoidTy(), 0)},
                false
        );

        threadedLoopBody = Function::Create(
                type,
                GlobalValue::ExternalLinkage,
                "ts", module.get()
        );
        threadedLoopBody->setDSOLocal(true);
        isCodegenThreadedLoopBody = true;
        auto entryBlock = BasicBlock::Create(context, "entry", threadedLoopBody);
        builder.SetInsertPoint(entryBlock);

        Function::arg_iterator actualArgs = threadedLoopBody->arg_begin();
        auto structLoc = &(*actualArgs);

        auto structPtrf = builder.CreateBitCast(structLoc, PointerType::get(this->varPassType, 0), "pass_var_struct");

        auto mStruct = builder.CreateStructGEP(structPtrf, 1);

        auto structPtr = builder.CreateBitCast(builder.CreateLoad(mStruct), PointerType::get(this->varPrivateType, 0),
                                               "private_var_struct");

        auto itr = 0;
        for (auto *ele: pVars) {
            auto x = dynamic_cast<VariableDerefNode *>(ele);
            auto var = builder.CreateStructGEP((structPtr), itr++);
            auto varPtrLoaded = builder.CreateLoad(var);
            auto varLoaded = builder.CreateLoad(varPtrLoaded);

            auto ftype = cxt->getFlareType(varLoaded);
            auto declared = new VarDeclNode(x->variableName.c_str(), ftype);
            if (ftype->getTypePrecedence() == VariableType::VARTYPE_ARRAY) {
                auto init = new EmptyNode(&(*varPtrLoaded));
                declared->setInitialValue(init);
            } else {
                auto init = new EmptyNode(&(*varLoaded));
                declared->setInitialValue(init);
            }

            dynamic_cast<StatementListNode *>(this->statementList)->pushFirst(declared);
        }

        this->statementList->codeGen(cxt);
        builder.CreateRet(nullptr);
        isCodegenThreadedLoopBody = false;

        return nullptr;
    }

    llvm::Value *LoopNode::codeGenCallThreadedLoopBody(Context *cxt) {

        auto pVarsStruct = new AllocaInst(
                this->varPrivateType,
                0,
                "passVar",
                cxt->getBuilder()->GetInsertBlock()
        );

        std::vector<llvm::Type *> items;
        auto pVars = this->analyzer->getPrivatizationVars();
        auto i = 0;
        for (auto *ele: pVars) {
            auto x = dynamic_cast<VariableDerefNode *>(ele);
            VarDeclNode *vNode = globalContext->findVariable(x->variableName);
            auto varVal = (vNode->getLLVMVarRef());
            auto varRef = builder.CreateStructGEP(pVarsStruct, i);
            builder.CreateStore(varVal, varRef);
            i += 1;
        }

        auto pvarsBcasted = builder.CreateBitCast(pVarsStruct, PointerType::get(builder.getVoidTy(), 0));

        createCall(cxt, "createTask", cxt->getBuilder()->getVoidTy(), {
                threadedLoopBody->getType(),
                PointerType::get(builder.getVoidTy(), 0)
        }, {threadedLoopBody, pvarsBcasted}, false);

        return nullptr;
    }
}
