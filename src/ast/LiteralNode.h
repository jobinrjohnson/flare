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
            INTEGER, DOUBLE, BOOLEAN, STRING
        } literalType;

        union LValue {
            int iVal;
            double dVal;
            bool bVal;
            char* sVal;
        } nodeValue;

    public:

        NodeType getNodeType();

        LiteralNode(int mLiteralValue);

        LiteralNode(double mLiteralValue);

        LiteralNode(char* mLiteralValue);

        LiteralNode(bool mLiteralValue);

        llvm::Value *codeGen(Context *cxt);


    };

}


#endif //FLARE_LITERALNODE_H
