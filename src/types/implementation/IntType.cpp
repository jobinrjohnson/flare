//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/IntType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *IntType::createInstance(Context *context, LValue val) {
        return llvm::ConstantInt::get(*context->getLLVMContext(), APInt(64, val.iVal));
    }

    Type *IntType::getLLVMType(Context *context) {
        return Type::getInt64Ty(*context->getLLVMContext());
    }
}
