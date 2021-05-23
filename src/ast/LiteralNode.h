//
// Created by jobinrjohnson on 7/22/20.
//

#ifndef FLARE_LITERALNODE_H
#define FLARE_LITERALNODE_H


#include "Node.h"

namespace flare::ast {

    class LiteralNode : public Node {

    protected:
        // Type of the literal
        VariableType literalType;

        // Value
        union LValue {
            int iVal;       // integer value
            double dVal;    // double value
            bool bVal;      // boolean value
            char *sVal;     // string value
        } nodeValue;

    public:

        NodeType getNodeType() override {
            return NodeType::LITERAL_NODE;
        }

        // integer constructor
        LiteralNode(int mLiteralValue);

        // decimal constructor
        LiteralNode(double mLiteralValue);

        // string constructor
        LiteralNode(char *mLiteralValue);

        // boolean constructor
        LiteralNode(bool mLiteralValue);

        // Returns the variable type
        VariableType getVarType();

        // Node:codegen override
        llvm::Value *codeGen(Context *cxt) override;


    };

}


#endif //FLARE_LITERALNODE_H
