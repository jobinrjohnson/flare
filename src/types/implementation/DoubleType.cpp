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

    Value *DoubleType::apply(Context *cxt, OperatorType symbol, Value *primary, Value *secondary) {
        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(cxt, secondary, VariableType::VARTYPE_DOUBLE);

        auto builder = cxt->getBuilder();

        llvm::Value *value;
        switch (symbol) {
            // Arithmetic operators
            case PLUS:
                value = builder->CreateFAdd(lhs, rhs, "mAdd");
                break;
            case MINUS:
                value = builder->CreateFSub(lhs, rhs, "mSub");
                break;
            case MUL:
                value = builder->CreateFMul(lhs, rhs, "mMul");
                break;
            case MODULO_DIV:
                throw "this cant happen";
                break;
            case DIV:
                value = builder->CreateFDiv(lhs, rhs, "mDiv");
                break;
            case UNARY_MINUS:
                value = builder->CreateFSub(rhs, lhs, "mUmin");
                break;
                // Boolean operators
            case LESS_THAN:
                value = builder->CreateFCmpOLT(lhs, rhs, "mAdd");
                break;
            case GREATER_THAN: // TODO remaining
                return builder->CreateFCmpOGT(lhs, rhs, "mGt");
            case GREATER_THAN_EQUAL:
                value = builder->CreateFCmpOGE(lhs, rhs, "mGte");
                break;
            case LESS_THAN_EQUAL:
                return builder->CreateFCmpOLE(lhs, rhs, "mLte");
            case EQUALITY:
                return builder->CreateFCmpOEQ(lhs, rhs, "mEq");
            case NOT_EQUALITY:
                return builder->CreateFCmpONE(lhs, rhs, "mNeq");
            default:
                throw "Not handled";
        }
        return value;
    }

    Value *DoubleType::getValue(Context *cxt, Value *value, VariableType valueType) {

        auto builder = cxt->getBuilder();

        switch (valueType) {
            case VariableType::VARTYPE_INT:
            case VariableType::VARTYPE_INT_64:
                return builder->CreateFPToSI(value, builder->getInt64Ty());
            case VARTYPE_INT_32:
                return builder->CreateFPToSI(value, builder->getInt32Ty());
            case VARTYPE_FLOAT:
                return builder->CreateSIToFP(value, builder->getFloatTy());
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return value;
            case VARTYPE_BOOLEAN:
                return builder->CreateFPToSI(value, builder->getInt1Ty());
            case VARTYPE_ARRAY:
            case VARTYPE_STRING:
            case VARTYPE_VOID:
            case OTHER:
                break;
        }
        throw "Conversion not defined";
    }
}
