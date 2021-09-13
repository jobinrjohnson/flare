//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_LOOPNODE_H
#define FLARE_LOOPNODE_H


#include "Node.h"

namespace flare::ast {
    class LoopNode : public Node {

        Node *statementList;
        Node *condition;

    public:

        Node *preLoop;
        Node *postLoop;

        Node *before;

        Node *after;

        NodeType getNodeType() override;

        LoopNode(Node *cond, Node *smt);

        llvm::Value *codeGen(Context *cxt) override;

        ~LoopNode() {
            delete (statementList);
            delete (condition);
        }


    };
}


#endif //FLARE_LOOPNODE_H
