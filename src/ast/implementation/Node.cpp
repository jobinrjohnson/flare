//
// Created by jobinrjohnson on 7/4/20.
//

#include <ast/Node.h>

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
std::unique_ptr<llvm::Module> module;

namespace ast {

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
}