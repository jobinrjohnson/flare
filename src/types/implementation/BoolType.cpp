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

    Value *BoolType::apply(Context *cxt, OperatorType symbol, Value *primary, Value *secondary) {
        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(cxt, secondary, VariableType::VARTYPE_BOOLEAN);
        auto builder = cxt->getBuilder();
        switch (symbol) {
            case EQUALITY:
                return builder->CreateICmpEQ(lhs, rhs);
            case NOT_EQUALITY:
                return builder->CreateICmpNE(lhs, rhs);
            case LOGICAL_AND:
                return builder->CreateAnd(lhs, rhs);
            case LOGICAL_OR:
                return builder->CreateOr(lhs, rhs);
                // Arithmetic operators
            case PLUS:
            case MINUS:
            case MUL:
            case MODULO_DIV:
            case DIV:
            case UNARY_MINUS:
                // Relational operators
            case LESS_THAN:
            case GREATER_THAN:
            case GREATER_THAN_EQUAL:
            case LESS_THAN_EQUAL:
            default:
                break;
        }
        throw "Operation not supported on boolean type";
    }


    Value *BoolType::getValue(Context *cxt, Value *value, VariableType valueType) {

        auto builder = cxt->getBuilder();

        switch (valueType) {
            case VariableType::VARTYPE_INT:
            case VariableType::VARTYPE_INT_64:
                return builder->CreateIntCast(value, builder->getInt64Ty(), false);
            case VARTYPE_INT_32:
                return builder->CreateIntCast(value, builder->getInt32Ty(), false);
            case VARTYPE_FLOAT:
                return builder->CreateUIToFP(value, builder->getFloatTy());
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return builder->CreateUIToFP(value, builder->getDoubleTy());
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

