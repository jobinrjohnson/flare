//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/BoolType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *BoolType::createInstance(LValue val) {
        auto var = this->cxt->getBuilder()->CreateAlloca(this->getLLVMType());
        if (this->cxt->getBuilder()->GetInsertBlock() != nullptr) {
            builder.CreateStore(this->createValue(val), var);
        }
        return var;
    }

    Value *BoolType::createValue(LValue val) {
        return llvm::ConstantInt::get(*this->cxt->getLLVMContext(), APInt(1, val.bVal));
    }

    Type *BoolType::probeLLVMType() {
        return Type::getInt1Ty(*this->cxt->getLLVMContext());
    }

    Type *BoolType::getLLVMPtrType() {
        return nullptr;
    }

    Value *BoolType::getDefaultValue() {
        LValue lValue = {
                .bVal = false
        };
        return this->createValue(lValue);
    }

    // Binary operators
    Value *BoolType::apply(OperatorType symbol, Value *primary, Value *secondary) {
        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(secondary, VariableType::VARTYPE_BOOLEAN);
        auto builder = cxt->getBuilder();
        switch (symbol) {
            case ASSIGNMENT:
                return builder->CreateStore(rhs, lhs);
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

    // Unary operators
    Value *BoolType::apply(OperatorType symbol, Value *primary) {
        if (symbol == OperatorType::NOT) {
            return builder.CreateNot(primary);
        }
        throw "Operation not supported on boolean type";
    }


    Value *BoolType::getValue(Value *value, VariableType valueType) {

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

    Value *BoolType::apply(OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }
}

