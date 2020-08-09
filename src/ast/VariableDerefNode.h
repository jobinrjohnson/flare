//
// Created by jobinrjohnson on 8/3/20.
//

#ifndef FLARE_VARIABLEDEREFNODE_H
#define FLARE_VARIABLEDEREFNODE_H


#include "Node.h"

namespace ast {
    class VariableDerefNode : public Node {

    protected:

        std::string variableName;

    public:

        NodeType getNodeType() {
            return VAR_DEREF_NODE;
        }

        VariableDerefNode(char *mLiteralValue) {
            this->variableName = mLiteralValue;
        }

        llvm::Value *codeGen(int depth) {
            this->printCallStack(depth, "VariableDerefNode", __FUNCTION__);

            auto gVar = module->getNamedGlobal(this->variableName);
            if (!gVar) {
                throw "no global variable declared with the name"; // TODO throw proper error
            }

            return builder.CreateLoad(gVar, this->variableName);

        }


    };
}


#endif //FLARE_VARIABLEDEREFNODE_H
