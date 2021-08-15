//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/DoubleType.h"

#include <ast/helpers/Context.h>

namespace flare::types {

    Value *DoubleType::createInstance(LValue val) {
        auto var = this->cxt->getBuilder()->CreateAlloca(this->getLLVMType());
        if (this->cxt->getBuilder()->GetInsertBlock() != nullptr) {
            builder.CreateStore(this->createValue(val), var);
        }
        return var;
    }

    Value *DoubleType::createValue(LValue val) {
        return ConstantFP::get(*this->cxt->getLLVMContext(), APFloat(val.dVal));
    }

    Type *DoubleType::probeLLVMType() {
        return Type::getDoubleTy(*this->cxt->getLLVMContext());
    }

    Type *DoubleType::getLLVMPtrType() {
        return nullptr;
    }

    Value *DoubleType::getDefaultValue() {
        LValue lValue = {
                .dVal = 0.00
        };
        return this->createValue(lValue);
    }

    Value *DoubleType::apply(OperatorType symbol, Value *primary, Value *secondary) {
        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(secondary, VariableType::VARTYPE_DOUBLE);

        auto builder = cxt->getBuilder();

        llvm::Value *value;
        switch (symbol) {
            case ASSIGNMENT:
                return builder->CreateStore(rhs, lhs);
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

    Value *DoubleType::getValue(Value *value, VariableType valueType) {

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

    Value *DoubleType::apply(OperatorType symbol, Value *primary) {
        if (symbol == OperatorType::NOT) {
            return builder.CreateNot(primary);
        }
        throw "Operation not supported on boolean type";
    }

    Value *DoubleType::apply(OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }

}
