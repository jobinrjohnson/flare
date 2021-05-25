//
// Created by jobinrjohnson on 7/23/20.
//

#include <ast/helpers/VariableHelper.h>
#include <exceptions/SemanticException.h>
#include <ast/VarDeclNode.h>
#include <ast/StatementListNode.h>
#include <ast/ClassDeclNode.h>

namespace flare::ast {


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
        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());

        // If there is no initial value specified at the declaration of the variable.
        if (this->initialValue == nullptr) {
            // If there is no initial value just return the created variable.
            Type *variableType = getLLVMType(this->type->type, context);
            this->llvmVarRef = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
            currentBlock->createLocal(this->variableName, this);
            return this->llvmVarRef;
        }

        Value *initializerValue = this->initialValue->codeGen(cxt);

        Type *variableType;
        // If type is explicitly specified use that for declaration
        if (this->type != nullptr) {
            variableType = this->getVariableLLVMType();
        } else {
            variableType = initializerValue->getType();
        }

        this->llvmVarRef = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
        currentBlock->createLocal(this->variableName, this);

        // if initializer type and variable type mismatches. cast the initializer type to the variable's type
        if (this->type != nullptr && initializerValue->getType() != variableType) {
            initializerValue = castTo(initializerValue, this->type);
        }

        // Store and return
        return builder.CreateStore(initializerValue, this->llvmVarRef);
    }

    llvm::Value *VarDeclNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VarDeclNode", __FUNCTION__);

        if (this->isClassVariable()) {
            throw "Class variable functionality not implemented.";
        }

        auto *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
        if (currentBlock != nullptr && currentBlock->findLocal(this->variableName) != nullptr) {

            throw new flare::exceptions::SemanticException("variable with name : '"
                                                           + this->variableName
                                                           + "' already exists in this block",
                                                           this->lineNumber
            );

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

    llvm::Type *VarDeclNode::getVariableLLVMType() {

        // TODO deal with type from initializer

        if (this->type == nullptr) {

            throw new exceptions::SemanticException("variable : '"
                                                    + this->variableName
                                                    + "' has no initializer or explicit type definition",
                                                    this->lineNumber
            );

        }

        if (this->type->type == VariableType::VARTYPE_OBJECT) {
            ClassDeclNode *cNode = dynamic_cast<ClassDeclNode *>(this->type->typeRef->node);
            return cNode->getClassLLVMPointerType();
        }


        // If there is no initial value just return the created variable.
        return getLLVMType(this->type->type, context);
    }
}