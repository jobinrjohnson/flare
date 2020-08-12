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

        NodeType getNodeType() override;

        ValuePlaceholderNode(Value *tempValue);

        llvm::Value *codeGen(int depth) override;

    };

}

#endif //FLARE_VALUEPLACEHOLDERNODE_H
