//
// Created by jobinrjohnson on 12/05/21.
//

#include "ClassDeclNode.h"

NodeType ast::ClassDeclNode::getNodeType() {
    return EXPR_NODE;
}

ast::ClassDeclNode::ClassDeclNode(const char *name) {

}

llvm::Value *ast::ClassDeclNode::codeGen(ast::Context *cxt) {
    return nullptr;
}
