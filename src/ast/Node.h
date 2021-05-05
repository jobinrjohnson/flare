//
// Created by jobinrjohnson on 7/4/20.
//

#ifndef FLARE_NODE_H
#define FLARE_NODE_H

#define FLARE_DEBUG true

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


using namespace llvm;

extern llvm::LLVMContext context;
extern llvm::IRBuilder<> builder;
extern std::unique_ptr<llvm::Module> module;

enum NodeType {
    ASSIGNMENT_NODE,
    EXPR_NODE,
    STATEMENT_NODE,
    LITERAL_NODE,
    STATEMENT_LIST_NODE,
    VAR_DECL_NODE,
    VAR_DEREF_NODE,
    IF_NODE,
    LOG_NODE,
    FUNCTION_NODE,
    VALUE_PLACEHOLDER_NODE
};

namespace ast {

    class Node {

    public:

        void printCallStack(Context *, std::string className, std::string functionName);

        void printDebug(std::string str);

        void printLLVMir();

        virtual llvm::Value *codeGen(Context *) = 0;

        virtual NodeType getNodeType() = 0;

    };

}


#endif //FLARE_NODE_H
