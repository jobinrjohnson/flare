//
// Created by jobinrjohnson on 7/4/20.
//

#include "../Node.h"


llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
std::unique_ptr<llvm::Module> module;

namespace ast {

    void Node::printCallStack(int depth, std::string className, std::string functionName) {

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

    void Node::printDebug(std::string str) {
        std::cout << str << "\n\n";
        std::cout.flush();
    }

    void Node::printLLVMir() {

        module = std::make_unique<llvm::Module>("FlareTest", context);

        std::vector<llvm::Type *> argVector(0, llvm::Type::getDoubleTy(context));
        llvm::FunctionType *functionRetType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
                                                                      argVector, false);
        llvm::Function *function = llvm::Function::Create(functionRetType, llvm::GlobalValue::ExternalLinkage,
                                                          "main", module.get());

        llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(basicBlock);

        this->codeGen(0);

        builder.CreateRet(ConstantInt::get(context, APInt(32, 0)));
        llvm::verifyFunction(*function, &(llvm::errs()));

        std::cout << "========================================\n";
        module->print(llvm::outs(), nullptr);
        std::cout << "========================================\n\n";

        if (FLARE_DEBUG) {
            outs() << "\n\n";
        }

        int retVal = -1;
        InitializeNativeTarget();
        ExecutionEngine *EE = EngineBuilder(std::move(module)).create();
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

}