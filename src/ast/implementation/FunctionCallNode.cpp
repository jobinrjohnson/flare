//
// Created by jobinrjohnson on 08/05/21.
//

#include "FunctionCallNode.h"

llvm::Value *ast::FunctionCallNode::codeGen(ast::Context *cxt) {

    auto calleeFunction = module->getFunction(this->functionName);
    if (calleeFunction == nullptr) {
        throw "Function not declared in the scope";
    }
    // TODO handle args
    return builder.CreateCall(calleeFunction, None, this->functionName);

}

NodeType ast::FunctionCallNode::getNodeType() {
    return FUNCTION_CALL_NODE;
}

ast::FunctionCallNode::FunctionCallNode(std::string functionName) {
    this->functionName = functionName;
}
