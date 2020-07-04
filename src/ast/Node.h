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

static llvm::LLVMContext llvmContext;
static llvm::IRBuilder<> builder(llvmContext);
static std::unique_ptr<llvm::Module> modules;

namespace ast {

    class Node {

    private:

        int nodeType;
        // For Type 0
        int nodeValue;

        // For type 1
        Node *opA, *opB;
        char opr;

        // For type 2
        Node *mNode;


    protected:
        llvm::Value *codeGenConstNode() {
//            std::cout << "Constant : " << this->nodeValue << std::endl;
            return llvm::ConstantFP::get(llvmContext, llvm::APFloat((float) this->nodeValue));
        }

        llvm::Value *codeGenExprNode() {

            llvm::Value *l = this->opA->codeGen();
            llvm::Value *r = this->opB->codeGen();

//            std::cout << "Expression : " << this->opr << std::endl;

            return builder.CreateFAdd(l, r, "tmpAdd");

        }


    public:
        Node(int a) {

            this->nodeType = 0;

            this->nodeValue = a;

        }

        Node(char opr, Node *a, Node *b) {

            this->nodeType = 1;

            this->opA = a;
            this->opB = b;
            this->opr = opr;

        }

        Node(Node *a) {

            this->nodeType = 2;

            this->mNode = a;

        }

        llvm::Value *codeGen() {

            switch (this->nodeType) {
                case 0:
                    return this->codeGenConstNode();
                case 1:
                    return this->codeGenExprNode();
                case 2:
                    return mNode->codeGen();
                default:
                    throw "Invalid node type.";
            }

        }


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
