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

        NodeType getNodeType() {
            return STATEMENT_LIST_NODE;
        }

        StatementListNode() {}

        StatementListNode(Node *node) {
            this->statements.push_back(node);
        }

        void push(Node *node) {
            this->statements.push_back(node);
        }


        llvm::Value *codeGen(int depth) {

            this->printCallStack(depth,"StatementListNode", __FUNCTION__);

            Value *finalValue = nullptr;
            for (auto const &value:this->statements) {
                finalValue = value->codeGen(depth+1);
            }

            return finalValue;
        }

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
