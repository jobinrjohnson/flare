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

    class Context {

        std::stack<Node *> functions;

        std::map<std::string, Node *> classDeclarations;

        std::map<llvm::Type *, Node *> customTypesAvail;

        std::map<std::string, BaseType *> types;

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

        Node *findVariable(std::string name);

        void pushClassDeclaration(std::string, Node *);

        Node *findClassDeclaration(std::string);

        void addType(llvm::Type *type, Node *);

        Node *getType(llvm::Type *type);

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

        BaseType *getFlareType(Value* value);

        void initTypes();

    };
}


#endif //FLARE_CONTEXT_H
