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

namespace ast {

    class Node {

    private:

        int nodeType;

    public:

        virtual llvm::Value *codeGen() = 0;

        void printLLVMir() {

            modules = std::make_unique<llvm::Module>("FlareTest", llvmContext);

            std::vector<llvm::Type *> argVector(0, llvm::Type::getDoubleTy(llvmContext));
            llvm::FunctionType *functionRetType = llvm::FunctionType::get(llvm::Type::getFloatTy(llvmContext),
                                                                          argVector, false);
            llvm::Function *function = llvm::Function::Create(functionRetType, llvm::GlobalValue::ExternalLinkage,
                                                              "main", modules.get());

            llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(llvmContext, "entry", function);
            builder.SetInsertPoint(basicBlock);

            if (llvm::Value *ret = this->codeGen()) {
                builder.CreateRet(ret);
                llvm::verifyFunction(*function);
            }

            modules->print(llvm::errs(), nullptr);
        }


    };

}


#endif //FLARE_NODE_H
