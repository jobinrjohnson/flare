//
// Created by jobinrjohnson on 7/23/20.
//

#include <helpers/VariableHelper.h>
#include "VarDeclNode.h"
#include "StatementListNode.h"

namespace ast {


    NodeType VarDeclNode::getNodeType() {
        return VAR_DECL_NODE;
    }

    Value *VarDeclNode::codeGenArray() {

        // TODO refactor this
        // probably we should use stl vector

        std::vector<llvm::Constant *> initList;

        llvm::ArrayType *array = llvm::ArrayType::get(Type::getInt32Ty(context), 100); // TODO Properly initialize array
        llvm::Constant *initializer = llvm::ConstantArray::get(array, initList);

        llvm::Value *unitInitList = new llvm::GlobalVariable(*module,
                                                             array,
                                                             false,
                                                             llvm::GlobalValue::ExternalLinkage,
                                                             initializer,
                                                             this->variableName
        );

        return unitInitList;
    }

    llvm::Value *VarDeclNode::codeGenGlobalVariable(Context *cxt) {

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());

        Value *value = this->initialValue->codeGen(cxt);

        auto *gvar = new llvm::GlobalVariable(
                *module,
                value->getType(),
                false,
                llvm::GlobalValue::InternalLinkage,
                0,
                this->variableName);

        // TODO handle this.
        gvar->setInitializer(dyn_cast<Constant>(value));

        currentBlock->createLocal(this->variableName, gvar);

        return gvar;
    }


    llvm::Value *VarDeclNode::codeGenLocalVariable(Context *cxt) {
        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());

        // If there is no initial value specified at the declaration of the variable.
        if (this->initialValue == nullptr) {

            if (this->type == nullptr) {
                this->throwSemanticError("variable : '"
                                         + this->variableName
                                         + "' has no initializer or explicit type definition");
            }

            // If there is no initial value just return the created variable.
            Type *variableType = getLLVMType(this->type->type, context);
            auto localVar = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
            currentBlock->createLocal(this->variableName, localVar);
            return localVar;
        }

        Value *initializerValue = this->initialValue->codeGen(cxt);

        Type *variableType;
        // If type is explicitly specified use that for declaration
        if (this->type != nullptr) {
            variableType = getLLVMType(this->type->type, context);
        } else {
            variableType = initializerValue->getType();
        }

        auto localVar = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
        currentBlock->createLocal(this->variableName, localVar);

        // if initializer type and variable type mismatches. cast the initializer type to the variable's type
        if (this->type != nullptr && initializerValue->getType() != variableType) {
            initializerValue = castTo(initializerValue, this->type);
        }

        // Store and return
        return builder.CreateStore(initializerValue, localVar);
    }

    llvm::Value *VarDeclNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VarDeclNode", __FUNCTION__);

        if (this->isClassVariable()) {
            throw "Class variable functionality not implemented.";
        }

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
        if (currentBlock != nullptr && currentBlock->findLocal(this->variableName) != nullptr) {
            this->throwSemanticError("variable with name : '"
                                     + this->variableName
                                     + "' already exists in this block");
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

    VarDeclNode::VarDeclNode(char *name, VarType *type) {
        this->variableName.assign(name);
        this->setVarType(type);
    }
}