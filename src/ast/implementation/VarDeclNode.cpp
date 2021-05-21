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

    Value *VarDeclNode::codeGenBuiltInTy(Context *cxt) {

        Value *value = this->initialValue->codeGen(cxt);
        Type *variableType;
        if (this->type == nullptr) {
            variableType = value->getType();
        } else {
            variableType = getLLVMType(this->type->type, context);
        }

        StatementListNode *currentBlock = dynamic_cast<StatementListNode *>(cxt->getCurrentStatementList());
        if (currentBlock->findLocal(this->variableName) != nullptr) {
            throw "Variable already declared in the same block.";
        }

        if (cxt->getCurrentFunction() != nullptr) {
            auto localVar = new AllocaInst(variableType, 0, this->variableName, builder.GetInsertBlock());
            currentBlock->createLocal(this->variableName, localVar);

            if (this->type != nullptr && value->getType() != variableType) {
                value = castTo(value, this->type);
            }
            return builder.CreateStore(value, localVar);

        }

        llvm::GlobalVariable *gvar = new llvm::GlobalVariable(
                *module,
                value->getType(),
                false,
                llvm::GlobalValue::InternalLinkage,
                0,
                this->variableName);

        gvar->setInitializer(dyn_cast<Constant>(value));
        currentBlock->createLocal(this->variableName, gvar);

        return gvar;
    }


    llvm::Value *VarDeclNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VarDeclNode", __FUNCTION__);

        if (this->type->type == VARTYPE_ARRAY) {
            return this->codeGenArray();
        } else {
            return this->codeGenBuiltInTy(cxt);
        };

    }

    VarDeclNode::VarDeclNode(char *name) {
        this->variableName.assign(name);
    }

    VarDeclNode::VarDeclNode(char *name, VarType *type) {
        this->variableName.assign(name);
        this->setVarType(type);
    }
}