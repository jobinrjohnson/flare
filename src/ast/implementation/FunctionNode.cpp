//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/FunctionNode.h>
#include <ast/ClassDeclNode.h>
#include <exceptions/SemanticException.h>
#include <ast/EmptyNode.h>

namespace flare::ast {

    // Generate the function prototype
    FunctionType *FunctionNode::codeGenSignature(Context *cxt) {
        std::vector<Type *> argVector;

        if (this->isClassFunction()) {
            // If it is a class function add class type as the first parameter
            auto *cNode = dynamic_cast<ClassDeclNode *>(this->classNode);
            argVector.push_back(cNode->getClassLLVMPointerType());
        }

        // Fill in the parameter list
        if (this->parameterList != nullptr) {
            for (Parameter *element: *(this->parameterList)) {
                Type *varType = getLLVMType(element->type->type, context);
                argVector.push_back(varType);
            }
        }

        return FunctionType::get(
                getLLVMType(this->returnType->type, context),
                argVector,
                false
        );
    }

    Value *FunctionNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "FunctionNode", __FUNCTION__);

        BasicBlock *currentBlock = builder.GetInsertBlock();

        cxt->pushFunction(this);

        this->function = Function::Create(
                this->codeGenSignature(cxt),
                GlobalValue::ExternalLinkage,
                this->getQualifiedFunctionName(), module.get()
        );

        // Start inserting to the function entry block
        this->entryBlock = BasicBlock::Create(context, "entry", this->function);
        builder.SetInsertPoint(this->entryBlock);

        // Prepare parameters add to frame
        // copy arguments to the frame so that it can be accessed within the function

        Function::arg_iterator actualArgs = function->arg_begin();
        if (this->isClassFunction()) {

            auto *vType = new VarType{
                    .type = VariableType::VARTYPE_OBJECT,
                    .typeRef = new TypeReference{
                            .node = this->classNode
                    }
            };

            auto *varDeclNode = new VarDeclNode("this", vType);
            varDeclNode->setInitialValue(new EmptyNode(&(*actualArgs)));
            varDeclNode->setLineNumber(this->lineNumber);
            this->statementListNode->pushFirst(varDeclNode);

            ++actualArgs;
        }

        if (this->parameterList != nullptr) {
            for (Parameter *element: *(this->parameterList)) {
                auto *varDeclNode = new VarDeclNode(element->name.c_str(), element->type);
                varDeclNode->setInitialValue(new EmptyNode(&(*actualArgs)));
                varDeclNode->setLineNumber(this->lineNumber);
                this->statementListNode->pushFirst(varDeclNode);
                ++actualArgs;
            }
        }

        // Original Function body.
        this->statementListNode->codeGen(cxt);

        // The function exit part
        this->codeGenExit(cxt);

        // TODO handle this properly.
        verifyFunction(*function, &(errs()));

        cxt->popFunction();

        if (currentBlock != nullptr) {
            builder.SetInsertPoint(currentBlock);
        }

        return this->function;
    }


    Value *FunctionNode::codeGenExit(Context *cxt) {

        // If there is no terminator
        if (builder.GetInsertBlock()->getTerminator() == nullptr) {

            if (this->exitBlock != nullptr) {
                // If there is an exit block branch to it if there is no terminator
                builder.CreateBr(this->exitBlock);
            } else {
                // If there is none we have to validate the return types and throw proper error
                if (this->returnType->type == VariableType::VARTYPE_VOID) {
                    builder.CreateRet(nullptr);
                } else {
                    throw new exceptions::SemanticException("Function '"
                                                            + this->getQualifiedFunctionName()
                                                            + "' should return a value",
                                                            this->lineNumber);
                }
            }
        }

        if (this->exitBlock != nullptr) {
            // TODO handle no return value defined.
            builder.SetInsertPoint(this->exitBlock);
            Value *returnValue = builder.CreateLoad(this->retValue);
            builder.CreateRet(returnValue);
        }

        return this->function;
    }

    FunctionNode::FunctionNode(const char *name, StatementListNode *statements, VarType *type) {
        this->name = name;
        this->statementListNode = statements;
        this->setReturnType(type);
    }

    FunctionNode::FunctionNode(const char *name, StatementListNode *statements, VarType *type,
                               std::vector<Parameter *> *parameterList) {
        this->name = name;
        this->statementListNode = statements;
        this->parameterList = parameterList;
        this->setReturnType(type);
    }

    FunctionNode::~FunctionNode() {
        free(this->statementListNode);
        free(this->classNode);
        for (auto ele : *(this->parameterList)) {
            free(ele);
        }
        free(this->parameterList);
    }

    Value *FunctionNode::setFunctionReturn(Value *returnValue) {

        // TODO move to assignment node
        if (this->function->getReturnType() != returnValue->getType()) {
            returnValue = castTo(returnValue, this->getReturnType());
        }

        if (builder.GetInsertBlock() == this->entryBlock) {

            // If the current block is insert block. this means this the only exit point
            // from the function. So we return the value in the current block ie, the entry block
            // and exit right away
            return builder.CreateRet(returnValue);
        } else {

            // This means the function has branches so we need to have an exit block
            // and branch to the the exit block after storing the return value to the return
            // value variable.
            if (this->exitBlock == nullptr) {

                // If exit block is not defined create exit block. Create a return block and place
                // it just inside the entry block.
                this->exitBlock = BasicBlock::Create(context, "exit", this->function);
                // Prepare return value
                // Insert it just before the entry block terminator
                this->retValue = new AllocaInst(
                        function->getReturnType(),
                        0,
                        ".retVal",
                        this->entryBlock->getTerminator()
                );
            }
            builder.CreateStore(returnValue, this->retValue);
            return builder.CreateBr(this->exitBlock);
        }

    }

    std::string FunctionNode::getQualifiedFunctionName() {

        if (this->isClassFunction()) {
            return dynamic_cast<ClassDeclNode *>(this->classNode)
                           ->getQualifiedClassName() +
                   "::" + this->name;
        }

        return this->name;
    }

}
