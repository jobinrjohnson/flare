//
// Created by jobinrjohnson on 17/06/21.
//

#include "../TypeConvNode.h"

namespace flare::ast {

    TypeConvNode::TypeConvNode(Value *operand) {
        this->addOperand(operand);
    }

    NodeType TypeConvNode::getNodeType() {
        return NodeType::TYPE_CONV_NODE;
    }

    llvm::Value *TypeConvNode::codeGen(Context *cxt) {
        return nullptr;
    }

    Type *TypeConvNode::getTargetType() {

        if (!this->isExplicitTypeCast()) {
            return this->targetType;
        }


        return nullptr;
    }

}