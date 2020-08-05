//
// Created by jobinrjohnson on 7/22/20.
//

#ifndef FLARE_LITERALNODE_H
#define FLARE_LITERALNODE_H


#include "Node.h"

namespace ast {

    class LiteralNode : public Node {

    protected:
        int literalValue;

    public:

        NodeType getNodeType() {
            return LITERAL_NODE;
        }

        LiteralNode(int mLiteralValue) {
            this->literalValue = mLiteralValue;
        }

        llvm::Value *codeGen() {
            return llvm::ConstantInt::get(llvmContext, APInt(32, this->literalValue));
        }


    };

}


#endif //FLARE_LITERALNODE_H
