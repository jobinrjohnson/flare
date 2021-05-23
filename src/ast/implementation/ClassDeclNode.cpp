//
// Created by jobinrjohnson on 12/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/ClassDeclNode.h>

ast::NodeType ast::ClassDeclNode::getNodeType() {
    return CLASS_DECL_NODE;
}


llvm::Value *ast::ClassDeclNode::codeGen(ast::Context *cxt) {

    // TODO handle this properly
    auto items = {getLLVMType(VARTYPE_INT_32, context), getLLVMType(VARTYPE_INT_64, context),
                  getLLVMType(VARTYPE_DOUBLE, context)};


    auto type = llvm::StructType::create(context, items, this->className);
    auto inst = new AllocaInst(type, 0, this->className, builder.GetInsertBlock());
    builder.CreateLoad(inst);


    return nullptr;
}

ast::ClassDeclNode::ClassDeclNode(const char *name, std::vector<ast::Node *> *nodeList) {

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
            this->vars.push_back(varDeclNode);
            continue;
        }
    }

}
