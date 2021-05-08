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

        NodeType getNodeType() override;

        explicit FunctionNode(const char *name, StatementListNode *statements);

        llvm::FunctionType *codeGenSignature(Context *cxt);

        llvm::Value *codeGen(Context *cxt) override;

        void setHasMultipleExits();

    };
}


#endif //FLARE_FUNCTIONNODE_H
