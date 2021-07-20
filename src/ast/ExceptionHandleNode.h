//
// Created by jobinrjohnson on 27/06/21.
//

#ifndef FLARE_EXCEPTIONHANDLENODE_H
#define FLARE_EXCEPTIONHANDLENODE_H

#include "Node.h"
#include "StatementListNode.h"
#include <map>

namespace flare::ast {
    class ExceptionHandleNode : public Node {

        StatementListNode *tryBlock;

        std::map<VarType *, StatementListNode *> catchBlocks;

        StatementListNode *finallyNode;

    public:

        // Unwind block for invoke
        llvm::BasicBlock *exceptionBlock;

        NodeType getNodeType() override;

        explicit ExceptionHandleNode(StatementListNode *tryBlock);

        llvm::Value *codeGen(Context *cxt) override;

        void addCatchBlock(StatementListNode *catchBlock, VarType *type, std::string);

        llvm::Value *
        handleOperation(Context *, std::function<Value *(BasicBlock *normalBlock, BasicBlock *exceptionBlock)>);

        void setFinallyBlock(StatementListNode *);

    };
}

#endif //FLARE_EXCEPTIONHANDLENODE_H
