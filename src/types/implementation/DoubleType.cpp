//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/DoubleType.h"

#include <ast/helpers/Context.h>

namespace flare::types {

    Value *DoubleType::createInstance(Context *context, LValue val) {
        return ConstantFP::get(*context->getLLVMContext(), APFloat(val.dVal));
    }

    Type *DoubleType::getLLVMType(Context *context) {
        return Type::getDoubleTy(*context->getLLVMContext());
    }
}
