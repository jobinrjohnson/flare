//
// Created by jobinrjohnson on 8/8/20.
//

#ifndef FLARE_FLAREJIT_H
#define FLARE_FLAREJIT_H

#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

using namespace llvm;

namespace flare::jit {

    class FlareJit {

    protected:

        std::unique_ptr<Module> module;

        std::vector<GenericValue> execArgs;

        ExecutionEngine *EE;

        Function *execStartFunction;

        int exitCode = -1;

    public:


        explicit FlareJit(std::unique_ptr<Module> &module);

        ~FlareJit();

        void initialize();

        void setArg(GenericValue arg);

        int execute();

        int getExitCode();

    };
}

#endif //FLARE_FLAREJIT_H
