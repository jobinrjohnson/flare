//
// Created by jobinrjohnson on 8/8/20.
//

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ManagedStatic.h>
#include "FlareJit.h"

FlareJit::FlareJit(std::unique_ptr<Module> &module) {
    this->module = std::move(module);
}

void FlareJit::initialize() {
    InitializeNativeTarget();
    this->EE = EngineBuilder(std::move(module))
            .create();
}

void FlareJit::setArg(GenericValue arg) {
    this->execArgs.push_back(arg);
}

int FlareJit::execute() {
    llvm::Function *function = this->module->getFunction("main");

    GenericValue gv = this->EE->runFunction(
            function,
            this->execArgs
    );

    int retVal = (int) gv.IntVal.getZExtValue();
    delete this->EE;
    llvm_shutdown();
    return retVal;
}