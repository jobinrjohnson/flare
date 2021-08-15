//
// Created by jobinrjohnson on 06/08/21.
//

#include "types/ArrayType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *FArrayType::probeLLVMType() {
        std::vector<llvm::Type *> items = {
                this->cxt->getBuilder()->getInt8PtrTy()
        };
        auto arrayLLVMType = StructType::create(*this->cxt->getLLVMContext(), items, "FLARE_array_t");
        return PointerType::get(arrayLLVMType, 0);
    }

    Value *FArrayType::createInstance(LValue lVal) {
        auto builder = this->cxt->getBuilder();
        auto var = builder->CreateAlloca(this->getLLVMType());
        this->createCall("FLARE_arr_init", builder->getVoidTy(),
                         {PointerType::get(this->getLLVMType(), 0), builder->getInt64Ty()},
                         {var, ConstantInt::get(*this->cxt->getLLVMContext(), APInt(64, this->arrayType))});
        // TODO freeup allocated mem on out of scope
        return var;
    }

    Type *FArrayType::getLLVMPtrType() {
        return nullptr;
    }

    Value *FArrayType::getDefaultValue() {
        return nullptr;
    }

    Value *FArrayType::apply(OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *FArrayType::apply(OperatorType symbol, Value *primary) {
        return nullptr;
    }

    Value *FArrayType::getValue(Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *FArrayType::createValue(LValue) {
        return nullptr;
    }

    Value *FArrayType::apply(OperatorType symbol, std::vector<Value *> operands) {

        auto builder = cxt->getBuilder();

        switch (symbol) {
            case ASSIGNMENT: {
                return this->createCall("FLARE_arr_index_assign_" + getCFunctionBindingType(),
                                        builder->getVoidTy(),
                                        {this->getLLVMType(), builder->getInt64Ty(),
                                         cxt->getFlareType(this->arrayType)->getLLVMType()},
                                        {builder->CreateLoad(operands[0]), operands[1], operands[2]});
                break;
            }
            case OperatorType::VAR_DE_REF: {
                return this->createCall("FLARE_arr_index_deref_" + getCFunctionBindingType(),
                                        cxt->getFlareType(this->arrayType)->getLLVMType(),
                                        {this->getLLVMType(), builder->getInt64Ty()},
                                        {builder->CreateLoad(operands[0]), operands[1]});
            }
            default:
                break;
        }

        return nullptr;
    }

}
