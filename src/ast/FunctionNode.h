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
        bool hasMultipleExits = false;

    protected:
        Node *node;

        void prepareBlocks();

    public:

        BasicBlock *entryBlock;
        BasicBlock *exitBlock;
        Function *function;
        AllocaInst *retValue;

        NodeType getNodeType();

        explicit FunctionNode(const char *name, StatementListNode *statements);

        llvm::Value *codeGen(Context *cxt);

        void setHasMultipleExits();

    };
}


#endif //FLARE_FUNCTIONNODE_H
