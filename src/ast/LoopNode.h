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


        NodeType getNodeType() override;

        LoopNode(Node *cond, Node *smt);

        llvm::Value *codeGen(Context *cxt) override;


    };
}


#endif //FLARE_LOOPNODE_H
