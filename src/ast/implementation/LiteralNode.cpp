//
// Created by jobinrjohnson on 7/22/20.
//

#include <ast/LiteralNode.h>

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

    LiteralNode::LiteralNode(bool mLiteralValue) {
        this->nodeValue.bVal = mLiteralValue;
        this->literalType = BOOLEAN;
    }

    llvm::Value *LiteralNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "LiteralNode", __FUNCTION__);

        switch (this->literalType) {

            case INTEGER:
                return llvm::ConstantInt::get(context, APInt(64, this->nodeValue.iVal));
            case DOUBLE:
                return ConstantFP::get(Type::getDoubleTy(context), this->nodeValue.dVal);
            case BOOLEAN:
                return ConstantInt::get(context, APInt(1, this->nodeValue.iVal));
            case STRING:
                return builder.CreateGlobalStringPtr(StringRef(this->nodeValue.sVal));
            default:
                throw "Not handled"; // TODO throw errors properly

        }

    }

    LiteralNode::LiteralNode(char *mLiteralValue) {
        // TODO process string for escape sequence;
        this->nodeValue.sVal = mLiteralValue;
        this->literalType = STRING;
    }

}