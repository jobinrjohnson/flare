//
// Created by jobinrjohnson on 06/08/21.
//

#include "types/ArrayType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *FArrayType::probeLLVMType(Context *context) {
        std::vector<llvm::Type *> items = {
                context->getBuilder()->getInt8PtrTy()
        };
        auto arrayLLVMType = StructType::create(*context->getLLVMContext(), items, "FLARE_array_t");
        return PointerType::get(arrayLLVMType, 0);
    }

    Value *FArrayType::createInstance(Context *context, LValue lVal) {
        auto builder = context
                ->getBuilder();
        auto var = builder->CreateAlloca(this->getLLVMType(context));
        this->createCall(context, "FLARE_arr_init", builder->getVoidTy(),
                         {PointerType::get(this->getLLVMType(context), 0), builder->getInt64Ty()},
                         {var, ConstantInt::get(*context->getLLVMContext(), APInt(64, this->arrayType))});
        // TODO freeup allocated mem on out of scope
        return var;
    }

    Type *FArrayType::getLLVMPtrType(Context *) {
        return nullptr;
    }

    Value *FArrayType::getDefaultValue(Context *) {
        return nullptr;
    }

    Value *FArrayType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *FArrayType::apply(Context *cxt, OperatorType symbol, Value *primary) {
        return nullptr;
    }

    Value *FArrayType::getValue(Context *cxt, Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *FArrayType::createValue(Context *, LValue) {
        return nullptr;
    }

    Value *FArrayType::apply(Context *cxt, OperatorType symbol, std::vector<Value *> operands) {

        auto builder = cxt->getBuilder();

        switch (symbol) {
            case ASSIGNMENT: {
                return this->createCall(cxt, "FLARE_arr_index_assign_int", builder->getVoidTy(),
                                        {this->getLLVMType(cxt), builder->getInt64Ty(), builder->getInt64Ty()},
                                        {builder->CreateLoad(operands[0]), operands[1], operands[2]});
                break;
            }
            case OperatorType::VAR_DE_REF: {
                return this->createCall(cxt, "FLARE_arr_index_deref_int", builder->getInt64Ty(),
                                        {this->getLLVMType(cxt), builder->getInt64Ty()},
                                        {builder->CreateLoad(operands[0]), operands[1]});
            }
            default:
                break;
        }

        return nullptr;
    }

}
