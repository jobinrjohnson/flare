//
// Created by jobinrjohnson on 7/4/20.
//

#ifndef FLARE_NODE_H
#define FLARE_NODE_H

#include <iostream>

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Verifier.h"
#include "helpers/Context.h"
#include "constants/AstConstants.h"


using namespace llvm;

namespace flare::ast {

    class Node {

    protected:
        int lineNumber;
    public:

        void setLineNumber(int lNo) {
            this->lineNumber = lNo;
        }

        void printDebug(std::string str);

        void startCodeGen();

        virtual llvm::Value *codeGen(Context *) = 0;

        virtual NodeType getNodeType() = 0;

        void printCallStack(Context *, std::string className, std::string functionName);

        virtual ~Node() {};

    };

}


#endif //FLARE_NODE_H
