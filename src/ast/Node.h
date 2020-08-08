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

using namespace llvm;

static llvm::LLVMContext llvmContext;
static llvm::IRBuilder<> builder(llvmContext);
static std::unique_ptr<llvm::Module> modules;

enum NodeType {
    NODE,
    ASSIGNMENT_NODE,
    EXPR_NODE,
    LITERAL_NODE,
    STATEMENT_LIST_NODE,
    VAR_DECL_NODE,
    VAR_DEREF_NODE
};

namespace ast {

    class Node {

    private:

        int nodeType;

    public:

        void printDebug(std::string str) {
            std::cout << str << "\n\n";
            std::cout.flush();
        }

        virtual llvm::Value *codeGen() = 0;

        virtual NodeType getNodeType() = 0;

        void printLLVMir() {

            modules = std::make_unique<llvm::Module>("FlareTest", llvmContext);

            std::vector<llvm::Type *> argVector(0, llvm::Type::getDoubleTy(llvmContext));
            llvm::FunctionType *functionRetType = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext),
                                                                          argVector, false);
            llvm::Function *function = llvm::Function::Create(functionRetType, llvm::GlobalValue::ExternalLinkage,
                                                              "main", modules.get());

            llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(llvmContext, "entry", function);
            builder.SetInsertPoint(basicBlock);
            if (llvm::Value *ret = this->codeGen()) {
                builder.CreateRet(ret);
                if (!llvm::verifyFunction(*function, &(llvm::errs()))) {
                    std::cout << "llvm verification fail" << "\n\n\n";
                }
            }

            std::cout << "========================================\n";
            modules->print(llvm::outs(), nullptr);
            std::cout << "========================================\n\n";
        }


    };

}


#endif //FLARE_NODE_H
