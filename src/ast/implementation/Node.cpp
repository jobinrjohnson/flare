//
// Created by jobinrjohnson on 7/4/20.
//

#include "../Node.h"

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
std::unique_ptr<llvm::Module> module;

namespace ast {

    void Node::printCallStack(Context *cxt, std::string className, std::string functionName) {

#ifndef FLARE_DEBUG
        return;
#endif

//        int depth = cxt->depth;
//
//        while (depth > 0) {
//            if (depth == 1) {
//                std::cout << "|__";
//            } else {
//                std::cout << "|  ";
//            };
//            depth--;
//        }
        std::cout << className << "@" << functionName << std::endl;
    }

    void Node::printDebug(std::string str) {
        std::cout << str << "\n\n";
        std::cout.flush();
    }

    void Node::startCodeGen() {
        module = std::make_unique<llvm::Module>("FlareTest", context);

        auto *cxt = new Context();
        this->codeGen(cxt);
        free(cxt);
    }

    void Node::throwSemanticError(std::string error) {
        throw error;
    }

}