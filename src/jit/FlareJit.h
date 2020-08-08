//
// Created by jobinrjohnson on 8/8/20.
//

#ifndef FLARE_FLAREJIT_H
#define FLARE_FLAREJIT_H

#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

//namespace jit {

using namespace llvm;
//    using namespace llvm::orc;

class FlareJit {

public:


    FlareJit() {


    }


};


//}


#endif //FLARE_FLAREJIT_H
