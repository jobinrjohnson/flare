//
// Created by jobinrjohnson on 8/8/20.
//

#include <llvm/Support/DynamicLibrary.h>
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"

#include "FlareJit.h"


namespace flare::jit {

    FlareJit::FlareJit(std::unique_ptr<Module> &module) {
        this->module = std::move(module);
    }

    FlareJit::~FlareJit() {
        llvm_shutdown();
    }

    void FlareJit::initialize() {

        this->execStartFunction = module->getFunction("main");

        InitializeNativeTarget();
        this->EE = EngineBuilder(std::move(module))
                .create();

        sys::DynamicLibrary::LoadLibraryPermanently("../../cmake-build-debug/stdapi/capi/libcapi.so");

    }

    void FlareJit::setArg(GenericValue arg) {
        this->execArgs.push_back(arg);
    }

    int FlareJit::execute() {
        GenericValue gv = this->EE->runFunction(
                this->execStartFunction,
                this->execArgs
        );
        this->exitCode = (int) gv.IntVal.getZExtValue();
        return this->exitCode;
    }

    int FlareJit::getExitCode() {
        return this->exitCode;
    }

}
