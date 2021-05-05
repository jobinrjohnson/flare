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
        std::map<std::string, Value *> locals;
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

        llvm::Value *codeGen(Context *cxt) override;

        void setHasMultipleExits();

        void createLocal(const std::string &, Value *);

        Value *findLocal(const std::string &);

    };
}


#endif //FLARE_FUNCTIONNODE_H
