//
// Created by jobinrjohnson on 12/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/ClassDeclNode.h>

flare::ast::NodeType flare::ast::ClassDeclNode::getNodeType() {
    return CLASS_DECL_NODE;
}


llvm::Value *flare::ast::ClassDeclNode::codeGen(flare::ast::Context *cxt) {

    // Codegen for class variables
    std::vector<llvm::Type *> items;
    for (VarDeclNode *ele:this->vars) {
        items.push_back(ele->getVariableLLVMType());
    }

    // Create LLVM type
    this->LLVMType = StructType::create(context, items, this->className);

    // Codegen for class functions
    for (FunctionNode *ele:this->functions) {
        ele->codeGen(cxt);
    }

    return nullptr;
}

flare::ast::ClassDeclNode::ClassDeclNode(const char *name, std::vector<flare::ast::Node *> *nodeList) {

    this->className = name;

    for (Node *ele:(*nodeList)) {
        FunctionNode *functionNode = nullptr;
        if ((functionNode = dynamic_cast<FunctionNode *>(ele)) != nullptr) {
            functionNode->setClass(this);
            this->functions.push_back(functionNode);
            continue;
        }

        VarDeclNode *varDeclNode = nullptr;
        if ((varDeclNode = dynamic_cast<VarDeclNode *>(ele)) != nullptr) {
            varDeclNode->setClass(this);
            this->vars.push_back(varDeclNode);
            continue;
        }
    }

}

llvm::StructType *flare::ast::ClassDeclNode::getClassLLVMType() {
    if (this->LLVMType == nullptr) {
        throw "LLVM type not defined in the class. Please call codegen";
    }
    return this->LLVMType;
}
