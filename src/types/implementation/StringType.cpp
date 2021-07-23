//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/StringType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Type *StringType::probeLLVMType(Context *context) {
        return llvm::Type::getInt8PtrTy(*context->getLLVMContext());
    }

    Value *StringType::createInstance(Context *context, LValue lVal) {
        return context
                ->getBuilder()
                ->CreateGlobalStringPtr(StringRef(lVal.sVal), "str");
    }

    Type *StringType::getLLVMPtrType(Context *context) {
        return nullptr;
    }

    Value *StringType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .sVal = const_cast<char *>("")
        };
        return this->createInstance(cxt, lValue);
    }

    Value *StringType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *StringType::getValue(Context *cxt, Value *value, VariableType valueType) {
        return nullptr;
    }
}
