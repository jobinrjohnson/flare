//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/IntType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *IntType::createInstance(Context *context, LValue val) {
        return llvm::ConstantInt::get(*context->getLLVMContext(), APInt(64, val.iVal));
    }

    Type *IntType::probeLLVMType(Context *context) {
        return Type::getInt64Ty(*context->getLLVMContext());
    }

    Type *IntType::getLLVMPtrType(Context *context) {
        return Type::getInt8PtrTy(*context->getLLVMContext());
    }

    Value *IntType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .iVal = 0
        };
        return this->createInstance(cxt, lValue);
    }
}
