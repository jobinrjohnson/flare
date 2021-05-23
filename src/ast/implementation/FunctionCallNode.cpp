//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/FunctionCallNode.h>

llvm::Value *flare::ast::FunctionCallNode::codeGen(flare::ast::Context *cxt) {

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

flare::ast::NodeType flare::ast::FunctionCallNode::getNodeType() {
    return FUNCTION_CALL_NODE;
}

flare::ast::FunctionCallNode::FunctionCallNode(std::string functionName) {
    this->functionName = functionName;
}

flare::ast::FunctionCallNode::FunctionCallNode(std::string functionName, std::vector<ExprNode *> *argumentList) {
    this->functionName = functionName;
    this->argumentList = argumentList;
}
