//
// Created by jobinrjohnson on 18/06/21.
//

#include "types/BaseType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Value *BaseType::createCall(std::string name, Type *returnType, ArrayRef<Type *> paramTypes,
                                ArrayRef<Value *> args, bool isVarArg) {
        auto *f = FunctionType::get(
                returnType,
                paramTypes,
                isVarArg
        );
        auto function = module->getOrInsertFunction(name, f);
        return cxt->getBuilder()->CreateCall(function, args);
    }
}
