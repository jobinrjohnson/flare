//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_CONTEXT_H
#define FLARE_CONTEXT_H

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <llvm/IR/IRBuilder.h>
#include <types/BaseType.h>

#include "llvm/IR/Value.h"


extern llvm::LLVMContext context;
extern llvm::IRBuilder<> builder;
extern std::unique_ptr<llvm::Module> module;

using namespace flare::types;

namespace flare::ast {

    class Node;

    class VarDeclNode;

    class FunctionNode;

    class Context {

    public:

        std::stack<FunctionNode *> functions;

        std::map<std::string, BaseType *> types;

        Function *personalityFunction;


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

        void pushFunction(FunctionNode *);

        void popFunction();

        FunctionNode *getCurrentFunction();

        VarDeclNode *findVariable(std::string name);

        inline llvm::LLVMContext *getLLVMContext() {
            return &context;
        }

        inline llvm::IRBuilder<> *getBuilder() {
            return &builder;
        }


        BaseType *findType(std::string name);

        bool registerType(std::string name, BaseType *type);

        BaseType *getFlareType(VariableType type);

        BaseType *getFlareType(VarType type);

        BaseType *getFlareType(Value *value);

        void initTypes();

        Function *getPersonalityFunction();

    };
}


#endif //FLARE_CONTEXT_H
