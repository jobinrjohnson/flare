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

        VariableDerefNode(char *mLiteralValue) {
            this->variableName = mLiteralValue;
        }

        llvm::Value *codeGen() {
            return modules->getNamedGlobal(this->variableName);
        }


    };
}


#endif //FLARE_VARIABLEDEREFNODE_H
