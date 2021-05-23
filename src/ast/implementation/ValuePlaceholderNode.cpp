//
// Created by jobinrjohnson on 8/9/20.
//

#include <ast/ValuePlaceholderNode.h>

namespace flare::ast {

    NodeType ValuePlaceholderNode::getNodeType() {
        return VALUE_PLACEHOLDER_NODE;
    }

    ValuePlaceholderNode::ValuePlaceholderNode(Value *tempValue) {
        this->value = tempValue;
    }

    llvm::Value *ValuePlaceholderNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "ValuePlaceholderNode", __FUNCTION__);
        return this->value;
    }

}