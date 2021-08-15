//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/VoidType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *VoidType::createInstance(LValue val) {
        return nullptr;
    }

    Type *VoidType::probeLLVMType() {
        return Type::getVoidTy(*cxt->getLLVMContext());
    }


    Value *VoidType::createValue(LValue val) {
        return nullptr;
    }

    Type *VoidType::getLLVMPtrType() {
        return nullptr;
    }

    Value *VoidType::getDefaultValue() {
        return nullptr;
    }

    Value *VoidType::apply(OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *VoidType::getValue(Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *VoidType::apply(OperatorType symbol, Value *primary) {
        return nullptr;
    }

    Value *VoidType::apply(OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }
}