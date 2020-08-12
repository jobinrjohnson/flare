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


#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

extern llvm::LLVMContext context;
extern llvm::IRBuilder<> builder;
extern std::unique_ptr<llvm::Module> module;

enum NodeType {
    NODE,
    ASSIGNMENT_NODE,
    EXPR_NODE,
    LITERAL_NODE,
    STATEMENT_LIST_NODE,
    VAR_DECL_NODE,
    VAR_DEREF_NODE,
    IF_NODE,
    LOG_NODE,
    VALUE_PLACEHOLDER_NODE
};

namespace ast {

    class Node {

    private:

        int nodeType;

    public:

        void printCallStack(int depth, std::string className, std::string functionName);

        void printDebug(std::string str);

        void printLLVMir();

        virtual llvm::Value *codeGen(int depth) = 0;

        virtual NodeType getNodeType() = 0;

    };

}


#endif //FLARE_NODE_H
