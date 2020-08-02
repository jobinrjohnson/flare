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
        StatementListNode() {}

        StatementListNode(Node *node) {
            this->statements.push_back(node);
        }

        void push(Node *node) {
            this->statements.push_back(node);
        }

        llvm::Value *codeGen() {
            std::cout << "Calling StatementListNode@codegen" << "\n";
            llvm::Value *last = NULL;
            (new VarDeclNode("hello"))->codeGen();
            for (auto const &value:this->statements) {
                last = value->codeGen();
            }
            return last;
        }

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
