//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_STATEMENTLISTNODE_H
#define FLARE_STATEMENTLISTNODE_H


#include "Node.h"
#include "VarDeclNode.h"

namespace flare::ast {

    class StatementListNode : public Node {

    private:
        std::vector<Node *> statements;

        std::map<std::string, VarDeclNode *> locals;


    public:

        NodeType getNodeType();

        StatementListNode();

        StatementListNode(Node *node);

        void push(Node *node);

        void pushFirst(Node *node);

        llvm::Value *codeGen(Context *cxt);

        void createLocal(const std::string &, VarDeclNode *);

        VarDeclNode *findLocal(const std::string &);

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
