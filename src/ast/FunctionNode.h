//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_FUNCTIONNODE_H
#define FLARE_FUNCTIONNODE_H


#include "Node.h"
#include "StatementListNode.h"

namespace ast {
    class FunctionNode : public Node {

        StatementListNode *statementListNode;
        std::string name;

    protected:
        Node *node;

    public:

        NodeType getNodeType();

        explicit FunctionNode(const char *name, StatementListNode *statements);

        llvm::Value *codeGen(int depth);

    };
}


#endif //FLARE_FUNCTIONNODE_H
