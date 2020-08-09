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

        void printCallStack(int depth, std::string className, std::string functionName) {

            if (!FLARE_DEBUG) {
                return;
            }

            while (depth > 0) {
                if (depth == 1) {
                    std::cout << "|__";
                } else {
                    std::cout << "|  ";
                };
                depth--;
            }
            std::cout << className << "@" << functionName << std::endl;
        }

        void printDebug(std::string str) {
            std::cout << str << "\n\n";
            std::cout.flush();
        }

        virtual llvm::Value *codeGen(int depth) = 0;

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
            if (llvm::Value *ret = this->codeGen(0)) {
                builder.CreateRet(ret);
                llvm::verifyFunction(*function, &(llvm::errs()));
            }

//            std::cout << "========================================\n";
//            modules->print(llvm::outs(), nullptr);
//            std::cout << "========================================\n\n";

            if (FLARE_DEBUG) {
                outs() << "\n\n";
            }


            int retVal = -1;


            InitializeNativeTarget();
            ExecutionEngine *EE = EngineBuilder(std::move(modules)).create();
            std::vector<GenericValue> args;
            GenericValue gv = EE->runFunction(
                    function,
                    args
            );

            retVal = gv.IntVal.getZExtValue();

            outs() << "Exit code: " << retVal << "\n";
            delete EE;
            llvm_shutdown();


        }


    };

}


#endif //FLARE_NODE_H
