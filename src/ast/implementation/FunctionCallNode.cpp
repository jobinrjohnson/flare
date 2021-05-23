//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/FunctionCallNode.h>

llvm::Value *ast::FunctionCallNode::codeGen(ast::Context *cxt) {

    auto calleeFunction = module->getFunction(this->functionName);
    if (calleeFunction == nullptr) {
        throw "Function not declared in the scope";
    }
    if (argumentList == nullptr) {
        return builder.CreateCall(calleeFunction, None, this->functionName);
    }

    std::vector<Value *> calleeArgs;
    for (ExprNode *element: *(this->argumentList)) {
        calleeArgs.push_back(element->codeGen(cxt->nextLevel()));
    }

    return builder.CreateCall(calleeFunction, calleeArgs, this->functionName);

}

ast::NodeType ast::FunctionCallNode::getNodeType() {
    return FUNCTION_CALL_NODE;
}

ast::FunctionCallNode::FunctionCallNode(std::string functionName) {
    this->functionName = functionName;
}

ast::FunctionCallNode::FunctionCallNode(std::string functionName, std::vector<ExprNode *> *argumentList) {
    this->functionName = functionName;
    this->argumentList = argumentList;
}
