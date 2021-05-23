//
// Created by jobinrjohnson on 8/9/20.
//

#ifndef FLARE_VALUEPLACEHOLDERNODE_H
#define FLARE_VALUEPLACEHOLDERNODE_H

#include "Node.h"

namespace flare::ast {

    class ValuePlaceholderNode : public Node {

        Value *value;

    public:

        NodeType getNodeType() override;

        ValuePlaceholderNode(Value *tempValue);

        llvm::Value *codeGen(Context *cxt) override;

    };

}

#endif //FLARE_VALUEPLACEHOLDERNODE_H
