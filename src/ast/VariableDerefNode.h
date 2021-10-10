//
// Created by jobinrjohnson on 8/3/20.
//

#ifndef FLARE_VARIABLEDEREFNODE_H
#define FLARE_VARIABLEDEREFNODE_H


#include "Node.h"

namespace flare::ast {
    class VariableDerefNode : public Node {

    public:

        bool isArrayDeReference = false;
        std::string variableName;
        std::string base;
        Node *arrayIndex;

        NodeType getNodeType();

        VariableDerefNode(char *mLiteralValue);

        VariableDerefNode(const char *mLiteralValue, const char *base);

        VariableDerefNode(char *mLiteralValue, Node *index);

        llvm::Value *codeGen(Context *cxt);


        ~VariableDerefNode() {
            delete (arrayIndex);
        }


    };
}


#endif //FLARE_VARIABLEDEREFNODE_H
