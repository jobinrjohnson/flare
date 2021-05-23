//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_CONTEXT_H
#define FLARE_CONTEXT_H

#include <iostream>
#include <stack>
#include <vector>

#include "llvm/IR/Value.h"

namespace flare::ast {

    class Node;

    class Context {

        std::stack<Node *> functions;


    public:

        int depth = 0;

        std::vector<Node *> statementList;

        Context *nextLevel() {
            depth++;
            return this;
        }

        void pushStatementList(Node *);

        void popStatementList();

        Node *getCurrentStatementList();

        llvm::Value *findLocal();

        void pushFunction(Node *);

        void popFunction();

        Node *getCurrentFunction();

    };
}


#endif //FLARE_CONTEXT_H
