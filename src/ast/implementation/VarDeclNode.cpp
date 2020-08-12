//
// Created by jobinrjohnson on 7/23/20.
//

#include "VarDeclNode.h"


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

        int i = 100;

        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));
        initList.push_back(ConstantInt::get(Type::getInt32Ty(context), i++));

        llvm::ArrayType *array = llvm::ArrayType::get(Type::getInt32Ty(context), 10);
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

    Value *VarDeclNode::codeGenBuiltInTy(int depth) {

        llvm::GlobalVariable *gvar = new llvm::GlobalVariable(
                *module,
                llvm::Type::getInt32Ty(context),
                false,
                llvm::GlobalValue::CommonLinkage,
                0,
                this->variableName);

        Value *value = this->initialValue->codeGen(depth + 1);
        gvar->setInitializer(dyn_cast<Constant>(value));

        return gvar;
    }


    llvm::Value *VarDeclNode::codeGen(int depth) {
        this->printCallStack(depth, "VarDeclNode", __FUNCTION__);

        if (this->isArray) {
            return this->codeGenArray();
        } else {
            return this->codeGenBuiltInTy(depth);
        };

    }
}