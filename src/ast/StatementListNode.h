//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_STATEMENTLISTNODE_H
#define FLARE_STATEMENTLISTNODE_H


#include "Node.h"
#include "VarDeclNode.h"

namespace ast {

    class StatementListNode : public Node {

    private:
        std::vector<Node *> statements;


    public:

        NodeType getNodeType();

        StatementListNode();

        StatementListNode(Node *node);

        void push(Node *node);

        llvm::Value *codeGen(Context *cxt);

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
