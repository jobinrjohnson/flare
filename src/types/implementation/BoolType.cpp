//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/BoolType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *BoolType::createInstance(Context *context, LValue val) {
        return llvm::ConstantInt::get(*context->getLLVMContext(), APInt(1, val.bVal));
    }

    Type *BoolType::probeLLVMType(Context *context) {
        return Type::getInt1Ty(*context->getLLVMContext());
    }

    Type *BoolType::getLLVMPtrType(Context *) {
        return nullptr;
    }

    Value *BoolType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .bVal = false
        };
        return this->createInstance(cxt, lValue);
    }

    Value *BoolType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }


    Value *BoolType::getValue(Context *cxt, Value *value, VariableType valueType) {

        switch (valueType) {
            case VariableType::VARTYPE_INT:
            case VariableType::VARTYPE_INT_64:
                return cxt->getBuilder()->CreateIntCast(value, cxt->getBuilder()->getInt64Ty(), true);
            case VARTYPE_INT_32:
                return cxt->getBuilder()->CreateIntCast(value, cxt->getBuilder()->getInt32Ty(), true);
            case VARTYPE_FLOAT:
                return cxt->getBuilder()->CreateSIToFP(value, cxt->getBuilder()->getFloatTy());
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return cxt->getBuilder()->CreateSIToFP(value, cxt->getBuilder()->getDoubleTy());
            case VARTYPE_BOOLEAN:
                return value;
            case VARTYPE_ARRAY:
            case VARTYPE_STRING:
            case VARTYPE_VOID:
            case OTHER:
                break;
        }
        throw "Conversion not defined";
    }
}

