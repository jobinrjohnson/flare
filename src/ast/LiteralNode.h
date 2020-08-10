//
// Created by jobinrjohnson on 7/22/20.
//

#ifndef FLARE_LITERALNODE_H
#define FLARE_LITERALNODE_H


#include "Node.h"

namespace ast {

    class LiteralNode : public Node {

    protected:
        enum LiteralType {
            INTEGER, DOUBLE
        } literalType;

        union LValue {
            int iVal;
            double dVal;
        } nodeValue;

    public:

        NodeType getNodeType() {
            return LITERAL_NODE;
        }

        LiteralNode(int mLiteralValue) {
            this->nodeValue.iVal = mLiteralValue;
            this->literalType = INTEGER;
        }

        LiteralNode(double mLiteralValue) {
            this->nodeValue.dVal = mLiteralValue;
            this->literalType = DOUBLE;
        }

        llvm::Value *codeGen(int depth) {

            this->printCallStack(depth, "LiteralNode", __FUNCTION__);

            switch (this->literalType) {

                case INTEGER:
                    return llvm::ConstantInt::get(context, APInt(32, this->nodeValue.iVal));
                case DOUBLE:
                    std::cout << this->nodeValue.dVal << "====";
                    return ConstantFP::get(Type::getDoubleTy(context), this->nodeValue.dVal);
                default:
                    throw "Not handled"; // TODO throw errors properly

            }

        }


    };

}


#endif //FLARE_LITERALNODE_H
