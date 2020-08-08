//
// Created by jobinrjohnson on 8/8/20.
//

#ifndef FLARE_IFSTATEMENTNODE_H
#define FLARE_IFSTATEMENTNODE_H


#include "Node.h"

namespace ast {

    class IfStatementNode : public Node {

        Node *statementList;
        Node *condition;

    public:

        llvm::Value *codeGen() override {

            return nullptr;

        }

    };

}


#endif //FLARE_IFSTATEMENTNODE_H
