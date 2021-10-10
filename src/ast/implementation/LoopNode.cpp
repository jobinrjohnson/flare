//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/LoopNode.h>
#include <ast/FunctionNode.h>
#include <ast/VariableDerefNode.h>

namespace flare::ast {

    extern Context *globalContext;
    extern Node *mLoopNode;
    extern std::vector<Node *> lopStatementLists;


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
        auto entryBlock = BasicBlock::Create(context, "entry", threadedLoopBody);
        builder.SetInsertPoint(entryBlock);
        this->statementList->codeGen(cxt);
        builder.CreateRet(nullptr);

        return nullptr;
    }

    llvm::Value *LoopNode::codeGenCallThreadedLoopBody(Context *cxt) {

        createCall(cxt, "createThread", cxt->getBuilder()->getVoidTy(), {
                threadedLoopBody->getType()
        }, {threadedLoopBody}, false);

        return nullptr;
    }
}
