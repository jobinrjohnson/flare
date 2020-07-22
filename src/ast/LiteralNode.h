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

        LiteralNode(int mLiteralValue) {
            this->literalValue = mLiteralValue;
        }

        llvm::Value *codeGen() {
            return llvm::ConstantFP::get(llvmContext, llvm::APFloat((float) this->literalValue));
        }


    };

}


#endif //FLARE_LITERALNODE_H
