//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_LOOPNODE_H
#define FLARE_LOOPNODE_H


#include <ast/analyzer/LoopAnalyzer.h>
#include "Node.h"

namespace flare::ast {

    class LoopNode : public Node {

    public:

        Node *statementList;
        Node *condition;

        Function *threadedLoopBody;

        LoopAnalyzer *analyzer;

        BasicBlock *mergeBlock2;

        BasicBlock *conditionBlock2;

        Node *preLoop;
        Node *postLoop;

        Node *before;

        Node *after;

        NodeType getNodeType() override;

        LoopNode(Node *cond, Node *smt);

        llvm::Value *codeGen(Context *cxt) override;

        llvm::Value *codeGenThreadedLoopBody(Context *cxt);

        llvm::Value *codeGenCallThreadedLoopBody(Context *cxt);

        StructType *varPassType;

        StructType *varPrivateType;

        ~LoopNode() {
            delete (statementList);
            delete (condition);
        }


    };
}


#endif //FLARE_LOOPNODE_H
