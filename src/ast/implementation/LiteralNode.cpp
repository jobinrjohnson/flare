//
// Created by jobinrjohnson on 7/22/20.
//

#include "LiteralNode.h"

namespace ast {

    NodeType LiteralNode::getNodeType() {
        return LITERAL_NODE;
    }

    LiteralNode::LiteralNode(int mLiteralValue) {
        this->nodeValue.iVal = mLiteralValue;
        this->literalType = INTEGER;
    }

    LiteralNode::LiteralNode(double mLiteralValue) {
        this->nodeValue.dVal = mLiteralValue;
        this->literalType = DOUBLE;
    }

    llvm::Value *LiteralNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "LiteralNode", __FUNCTION__);

        switch (this->literalType) {

            case INTEGER:
                return llvm::ConstantInt::get(context, APInt(32, this->nodeValue.iVal));
            case DOUBLE:
                return ConstantFP::get(Type::getDoubleTy(context), this->nodeValue.dVal);
            default:
                throw "Not handled"; // TODO throw errors properly

        }

    }

}