//
// Created by jobinrjohnson on 7/4/20.
//

#include <ast/Node.h>

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
std::unique_ptr<llvm::Module> module;

namespace flare::ast {

    void Node::printDebug(std::string str) {
        std::cout << str << "\n\n";
        std::cout.flush();
    }

    void Node::startCodeGen() {
        module = std::make_unique<llvm::Module>("FlareTest", context);

        auto *cxt = new Context();
        cxt->initTypes();

        this->codeGen(cxt);
        delete (cxt);

    }

    void Node::printCallStack(Context *, std::string className, std::string functionName) {
        std::cout << className << "@" << functionName << std::endl;
    }
}