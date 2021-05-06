//
// Created by jobinrjohnson on 7/23/20.
//

#include "VarDeclNode.h"
#include "FunctionNode.h"


namespace ast {


    NodeType VarDeclNode::getNodeType() {
        return VAR_DECL_NODE;
    }

    VarDeclNode::VarDeclNode(char *name, bool isArray) {
        this->variableName.assign(name);
        this->initialValue = new ast::LiteralNode(0);
        this->isArray = isArray;
    }

    VarDeclNode::VarDeclNode(char *name, Node *initialValue, bool isArray) {
        this->variableName = name;
        this->initialValue = initialValue;
        this->isArray = isArray;
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

        auto currentFunction = cxt->getCurrentFunction();
        if (currentFunction != nullptr) {
            auto localVar = new AllocaInst(value->getType(), 0, this->variableName, builder.GetInsertBlock());
            currentFunction->createLocal(this->variableName, localVar);
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

        return gvar;
    }


    llvm::Value *VarDeclNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VarDeclNode", __FUNCTION__);

        if (this->isArray) {
            return this->codeGenArray();
        } else {
            return this->codeGenBuiltInTy(cxt);
        };

    }

    VarDeclNode::VarDeclNode(char *name) {
        this->variableName.assign(name);
    }

    void VarDeclNode::setInitializer(Node *initial) {
        this->initialValue = initial;
    }
}