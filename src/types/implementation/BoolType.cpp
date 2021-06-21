//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/BoolType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *BoolType::createInstance(Context *context, LValue val) {
        return llvm::ConstantInt::get(*context->getLLVMContext(), APInt(1, val.bVal));
    }

    Type *BoolType::getLLVMType(Context *context) {
        return Type::getInt1Ty(*context->getLLVMContext());
    }
}

