//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_CONTEXT_H
#define FLARE_CONTEXT_H

#include <iostream>
#include <stack>
//#include "../FunctionNode.h"

namespace ast {

    class FunctionNode;

    class Context {

        std::stack<FunctionNode *> functions;

    public:

        int depth = 0;

        Context *nextLevel() {
            depth++;
            return this;
        }

        void pushFunction(FunctionNode *);

        void popFunction();

        FunctionNode *getCurrentFunction();

    };
}


#endif //FLARE_CONTEXT_H
