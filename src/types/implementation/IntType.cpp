//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/IntType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Value *IntType::createInstance(Context *context, LValue val) {
        auto var = context->getBuilder()->CreateAlloca(this->getLLVMType(context));
        if (context->getBuilder()->GetInsertBlock() != nullptr) {
            builder.CreateStore(this->createValue(context, val), var);
        }
        return var;
    }


    Value *IntType::createValue(Context *context, LValue val) {
        return ConstantInt::get(*context->getLLVMContext(), APInt(64, val.iVal));
    }

    Type *IntType::probeLLVMType(Context *context) {
        return Type::getInt64Ty(*context->getLLVMContext());
    }

    Type *IntType::getLLVMPtrType(Context *context) {
        return Type::getInt8PtrTy(*context->getLLVMContext());
    }

    Value *IntType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .iVal = 0
        };
        return this->createValue(cxt, lValue);
    }

    Value *IntType::apply(Context *cxt, OperatorType symbol, Value *primary, Value *secondary) {
        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(cxt, secondary, VariableType::VARTYPE_INT);

//        BinaryOperator::Create(Instruction::Add,lhs, rhs);
        auto builder = cxt->getBuilder();

        llvm::Value *value;
        switch (symbol) {
            case ASSIGNMENT:
                return builder->CreateStore(rhs, lhs);
                // Arithmetic operators
            case PLUS:
                value = builder->CreateAdd(lhs, rhs);
                break;
            case MINUS:
                value = builder->CreateSub(lhs, rhs);
                break;
            case MUL:
                value = builder->CreateMul(lhs, rhs);
                break;
            case MODULO_DIV:
                value = builder->CreateSRem(lhs, rhs);
                break;
            case DIV:
                value = builder->CreateFDiv(lhs, rhs);
                break;
            case UNARY_MINUS:
                value = builder->CreateSub(rhs, lhs);
                break;
                // Boolean operators
            case LESS_THAN:
                value = builder->CreateICmpSLT(lhs, rhs);
                break;
            case GREATER_THAN: // TODO remaining
                return builder->CreateICmpSGT(lhs, rhs);
            case GREATER_THAN_EQUAL:
                value = builder->CreateICmpSGE(lhs, rhs);
                break;
            case LESS_THAN_EQUAL:
                return builder->CreateICmpSLE(lhs, rhs);
            case EQUALITY:
                return builder->CreateICmpEQ(lhs, rhs);
            case NOT_EQUALITY:
                return builder->CreateICmpNE(lhs, rhs);
            case LOGICAL_AND:
                return builder->CreateAnd(lhs, rhs);
            case LOGICAL_OR:
                return builder->CreateOr(lhs, rhs);
            default:
                throw "Not handled";
        }
        return value;
    }

    Value *IntType::getValue(Context *cxt, Value *value, VariableType valueType) {

        auto builder = cxt->getBuilder();
        switch (valueType) {
            case VariableType::VARTYPE_INT:
            case VariableType::VARTYPE_INT_64:
                return value;
            case VARTYPE_INT_32:
                return builder->CreateIntCast(value, builder->getInt32Ty(), true);
            case VARTYPE_FLOAT:
                return builder->CreateSIToFP(value, builder->getFloatTy());
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return builder->CreateSIToFP(value, builder->getDoubleTy());
            case VARTYPE_BOOLEAN:
                return builder->CreateIntCast(value, builder->getInt1Ty(), false);
            case VARTYPE_ARRAY:
            case VARTYPE_STRING:
            case VARTYPE_VOID:
            case OTHER:
                break;
        }
        throw "Conversion not defined";
    }

    Value *IntType::apply(Context *cxt, OperatorType symbol, Value *primary) {
        if (symbol == OperatorType::NOT) {
            return builder.CreateNot(primary);
        }
        throw "Operation not supported on boolean type";
    }

    Value *IntType::apply(Context *cxt, OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }

}
