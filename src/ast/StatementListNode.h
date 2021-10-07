//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_STATEMENTLISTNODE_H
#define FLARE_STATEMENTLISTNODE_H


#include "Node.h"
#include "VarDeclNode.h"

namespace flare::ast {

    class StatementListNode : public Node {

    public:
        std::vector<Node *> statements;

        std::map<std::string, VarDeclNode *> locals;

        NodeType getNodeType() override;

        StatementListNode();

        explicit StatementListNode(Node *node);

        void push(Node *node);

        void pushFirst(Node *node);

        llvm::Value *codeGen(Context *cxt) override;

        void createLocal(const std::string &, VarDeclNode *);

        VarDeclNode *findLocal(const std::string &);

        ~StatementListNode() override {
            for (auto ele : (this->statements)) {
                delete (ele);
            }
        }

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
