//
// Created by jobinrjohnson on 8/8/20.
//

#ifndef FLARE_IFSTATEMENTNODE_H
#define FLARE_IFSTATEMENTNODE_H


#include "Node.h"
#include "ValuePlaceholderNode.h"

namespace flare::ast {

    class IfStatementNode : public Node {

    public:
        std::vector<Node *> statementList;
        std::vector<Node *> condition;

        NodeType getNodeType() override;

        IfStatementNode(Node *cond, Node *smt);

        void addBranch(Node *cond, Node *smt);

        void addBranch(IfStatementNode *node);

        void addElseBranch(Node *smt);

        llvm::Value *codegenIfElseIf(Context *);

        llvm::Value *codeGen(Context *cxt) override;

        ~IfStatementNode() {
            for (auto ele : (this->statementList)) {
                delete (ele);
            }
            for (auto ele : (this->condition)) {
                delete (ele);
            }
        }

    };

}


#endif //FLARE_IFSTATEMENTNODE_H
