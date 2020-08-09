//
// Created by jobinrjohnson on 8/9/20.
//

#ifndef FLARE_VALUEPLACEHOLDERNODE_H
#define FLARE_VALUEPLACEHOLDERNODE_H

#include "Node.h"

namespace ast {

    class ValuePlaceholderNode : public Node {

        Value *value;

    public:

        NodeType getNodeType() override {
            return VALUE_PLACEHOLDER_NODE;
        }

        ValuePlaceholderNode(Value *tempValue) {
            this->value = tempValue;
        }


        llvm::Value *codeGen(int depth) override {
            this->printCallStack(depth, "ValuePlaceholderNode", __FUNCTION__);
            return this->value;
        }

    };

}

#endif //FLARE_VALUEPLACEHOLDERNODE_H
