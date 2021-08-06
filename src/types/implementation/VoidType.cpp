//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/VoidType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *VoidType::createInstance(Context *context, LValue val) {
        return nullptr;
    }

    Type *VoidType::probeLLVMType(Context *context) {
        return Type::getVoidTy(*context->getLLVMContext());
    }


    Value *VoidType::createValue(Context *context, LValue val) {
        return nullptr;
    }

    Type *VoidType::getLLVMPtrType(Context *) {
        return nullptr;
    }

    Value *VoidType::getDefaultValue(Context *) {
        return nullptr;
    }

    Value *VoidType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *VoidType::getValue(Context *cxt, Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *VoidType::apply(Context *cxt, OperatorType symbol, Value *primary) {
        return nullptr;
    }

    Value *VoidType::apply(Context *cxt, OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }
}