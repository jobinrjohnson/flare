//
// Created by jobinrjohnson on 7/23/20.
//

#include <exceptions/SemanticException.h>
#include <ast/VarDeclNode.h>
#include <ast/StatementListNode.h>
#include <types/BaseType.h>
#include <types/StringType.h>
#include <types/ArrayType.h>

using namespace flare::exceptions;

namespace flare::ast {


    NodeType VarDeclNode::getNodeType() {
        return VAR_DECL_NODE;
    }

    Value *VarDeclNode::codeGenArray(Context *cxt) {
        if (this->initialValue != nullptr) {
            this->llvmVarRef = this->initialValue->codeGen(cxt);
            auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
            currentBlock->createLocal(this->variableName, this);
            return this->llvmVarRef;
        }

        auto ft = new FArrayType(cxt);
        ft->setArrayType(this->type->subType);
        this->flareType = ft;
        cxt->registerType("array_1", this->flareType); // TODO naming

        LValue lv;
        this->llvmVarRef = this->flareType->createInstance(lv);

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
        currentBlock->createLocal(this->variableName, this);

        return this->llvmVarRef;

    }

    llvm::Value *VarDeclNode::codeGenGlobalVariable(Context *cxt) {

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());

        Value *value = this->initialValue->codeGen(cxt);

        this->llvmVarRef = new llvm::GlobalVariable(
                *module,
                value->getType(),
                false,
                llvm::GlobalValue::InternalLinkage,
                0,
                this->variableName);

        // TODO handle this.
        static_cast<GlobalVariable *>(this->llvmVarRef)->setInitializer(dyn_cast<Constant>(value));

        currentBlock->createLocal(this->variableName, this);

        return this->llvmVarRef;
    }


    llvm::Value *VarDeclNode::codeGenLocalVariable(Context *cxt) {

        Value *initializerValue = nullptr;

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());

        if (this->variableName == "this") {
            Type *variableType = this->flareType->getLLVMPtrType();
            this->llvmVarRef = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
            currentBlock->createLocal(this->variableName, this);
            initializerValue = this->initialValue->codeGen(cxt);
            builder.CreateStore(initializerValue, this->llvmVarRef);
            return this->llvmVarRef;
        }

        if (initialValue != nullptr) {
            initializerValue = this->initialValue->codeGen(cxt);
            types::BaseType *initializerType = cxt->getFlareType(initializerValue);

            // If it is already an alloc inst (in the case of class) just rename it to this.
            if (isa<AllocaInst>(initializerValue) && !dynamic_cast<StringType *>(initializerType)) {
                this->flareType = initializerType;
                this->llvmVarRef = initializerValue;
                currentBlock->createLocal(this->variableName, this);

                return this->llvmVarRef;
            }

            // If the assignment is illegal throw error
            if (this->type != nullptr && initializerType != cxt->getFlareType(*this->type)) {
                throw new SemanticException(
                        "Illegal assignment :  Types does not match",
                        this->lineNumber
                );
            }

            this->flareType = initializerType;
        } else {
            this->flareType = cxt->getFlareType(*this->type);
        }


        LValue lvl;
        this->llvmVarRef = this->flareType->createInstance(lvl);
        this->llvmVarRef->setName(this->variableName);

        currentBlock->createLocal(this->variableName, this);

        if (initialValue != nullptr) {
            this->getFlareType()->apply(OperatorType::ASSIGNMENT, this->llvmVarRef, initializerValue);
        }

        return this->llvmVarRef;

    }

    llvm::Value *VarDeclNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VarDeclNode", __FUNCTION__);

        if (this->isClassVariable()) {
            throw "Class variable functionality not implemented.";
        }

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
        if (currentBlock != nullptr && currentBlock->findLocal(this->variableName) != nullptr) {

            throw new SemanticException("variable with name : '"
                                        + this->variableName
                                        + "' already exists in this block",
                                        this->lineNumber
            );

        }

        if (this->flareType != nullptr) {
            FArrayType *x;
            if ((x = dynamic_cast<FArrayType *>(this->flareType)) != nullptr) {
                return this->codeGenArray(cxt);
            }
        }

        if (this->type != NULL && this->type->type == VariableType::VARTYPE_ARRAY) {
            return this->codeGenArray(cxt);
        }

        // global variable
        if (cxt->getCurrentFunction() == nullptr) {
            return this->codeGenGlobalVariable(cxt);
        }

        // Function variable.
        return this->codeGenLocalVariable(cxt);

    }

    VarDeclNode::VarDeclNode(char *name) {
        this->variableName.assign(name);
    }

    VarDeclNode::VarDeclNode(const char *name, VarType *type) {
        this->variableName.assign(name);
        this->setVarType(type);
    }

    llvm::Type *VarDeclNode::getVariableLLVMType(Context *cxt) {

        // TODO deal with type from initializer

        if (this->type == nullptr) {

            throw new SemanticException("variable : '"
                                        + this->variableName
                                        + "' has no initializer or explicit type definition",
                                        this->lineNumber
            );

        }

        if (this->flareType == nullptr) {
            this->flareType = cxt->getFlareType(*this->type);
        }

        // If there is no initial value just return the created variable.
        return this->flareType->getLLVMType();
    }

    VarDeclNode::VarDeclNode(const char *name, BaseType *type) {
        this->variableName.assign(name);
        this->flareType = type;
    }
}