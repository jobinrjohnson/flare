//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/StringType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Type *StringType::getLLVMType(Context *context) {
        return llvm::Type::getInt8PtrTy(*context->getLLVMContext());
    }

    Value *StringType::createInstance(Context *context, LValue lVal) {
        return context
                ->getBuilder()
                ->CreateGlobalStringPtr(StringRef(lVal.sVal), "str");
    }
}
