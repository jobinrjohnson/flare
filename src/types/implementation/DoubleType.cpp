//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/DoubleType.h"

#include <ast/helpers/Context.h>

namespace flare::types {

    Value *DoubleType::createInstance(Context *context, LValue val) {
        return ConstantFP::get(*context->getLLVMContext(), APFloat(val.dVal));
    }

    Type *DoubleType::probeLLVMType(Context *context) {
        return Type::getDoubleTy(*context->getLLVMContext());
    }

    Type *DoubleType::getLLVMPtrType(Context *) {
        return nullptr;
    }

    Value *DoubleType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .dVal = 0.00
        };
        return this->createInstance(cxt, lValue);
    }
}
