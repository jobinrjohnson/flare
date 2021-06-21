//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/VoidType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *VoidType::createInstance(Context *context, LValue val) {
        return nullptr;
    }

    Type *VoidType::getLLVMType(Context *context) {
        return Type::getVoidTy(*context->getLLVMContext());
    }
}