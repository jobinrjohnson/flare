//
// Created by jobinrjohnson on 25/05/21.
//

#ifndef FLARE_EMPTYNODE_H
#define FLARE_EMPTYNODE_H

#include "Node.h"

namespace flare::ast {

    class EmptyNode : public Node {

        Value *llvmValue;

    public:


        NodeType getNodeType() override {
            return NodeType::EMPTY_NODE;
        }

        EmptyNode(Value *value);

        llvm::Value *codeGen(Context *cxt) override;

        ~EmptyNode() override {

        }

    };

}


#endif //FLARE_EMPTYNODE_H
