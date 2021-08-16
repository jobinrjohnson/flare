//
// Created by jobinrjohnson on 05/05/21.
//

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
            // TODO refactor this
            auto *cNode = cxt->findType(dynamic_cast<ClassDeclNode *>(this->classNode)->getQualifiedClassName());
            argVector.push_back(cNode->getLLVMPtrType());
        }

        // Fill in the parameter list
        if (this->parameterList != nullptr) {
            for (Parameter *element: *(this->parameterList)) {
//                cxt->getFlareType(element->type->type)->getLLVMType(cxt);
                Type *varType = cxt->getFlareType(
                        element->type->type)->getLLVMType(); //getLLVMType(element->type->type, context);
                argVector.push_back(varType);
            }
        }

        return FunctionType::get(
                cxt->getFlareType(this->returnType->type)->getLLVMType(),
                argVector,
                false
        );
    }

    Value *FunctionNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "FunctionNode", __FUNCTION__);

        BasicBlock *currentBlock = builder.GetInsertBlock();

        this->function = Function::Create(
                this->codeGenSignature(cxt),
                GlobalValue::ExternalLinkage,
                this->getQualifiedFunctionName(), module.get()
        );
        this->function->setDSOLocal(true);

        if (this->statementListNode == nullptr) {
            return this->function;
        }

        cxt->pushFunction(this);

        // Start inserting to the function entry block
        this->entryBlock = BasicBlock::Create(context, "entry", this->function);
        builder.SetInsertPoint(this->entryBlock);

        // Prepare parameters add to frame
        // copy arguments to the frame so that it can be accessed within the function

        Function::arg_iterator actualArgs = function->arg_begin();
        if (this->isClassFunction()) {
            // TODO refactor this
            auto *cBType = cxt->findType(dynamic_cast<ClassDeclNode *>(this->classNode)->getQualifiedClassName());
            auto *varDeclNode = new VarDeclNode("this", cBType);
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

    FunctionNode::FunctionNode(const char *name, VarType *type) {
        this->name = name;
        this->statementListNode = nullptr;
        this->setReturnType(type);
    }

    Value *FunctionNode::setFunctionReturn(Value *returnValue) {

        // TODO move to assignment node
//        if (this->function->getReturnType() != returnValue->getType()) {
//            throw "Return type mismatch";
//            // returnValue = castTo(returnValue, this->getReturnType());
//        }

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
                        this->entryBlock->getFirstNonPHI()
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

    FunctionNode::FunctionNode(const char *name, VarType *type, std::vector<Parameter *> *parameterList) {
        this->statementListNode = nullptr;
        this->name = name;
        this->parameterList = parameterList;
        this->setReturnType(type);
    }

    ExceptionHandleNode *FunctionNode::getExceptionHandler() {
        return this->exceptionHandlers.top();
    }

    void FunctionNode::pushExceptionHandler(ExceptionHandleNode *node) {
        this->exceptionHandlers.push(node);
    }

    void FunctionNode::popExceptionHandler() {
        this->exceptionHandlers.pop();
    }

    bool FunctionNode::hasExceptionHandler() {
        return !this->exceptionHandlers.empty();
    }

}
