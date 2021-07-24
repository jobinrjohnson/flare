//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/StringType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Type *StringType::probeLLVMType(Context *context) {
        std::vector<llvm::Type *> items = {
                context->getBuilder()->getInt8PtrTy(),
                context->getBuilder()->getInt64Ty()
        };
        auto stringLLVMType = StructType::create(*context->getLLVMContext(), items, "FLARE_string_t");
        return stringLLVMType;
    }

    Value *StringType::createInstance(Context *context, LValue lVal) {

        auto builder = context
                ->getBuilder();

        auto var = builder->CreateAlloca(this->getLLVMType(context));

        auto *f = FunctionType::get(
                builder->getVoidTy(),
                {builder->getInt8PtrTy(), builder->getInt8PtrTy()},
                false
        );
        auto initFun = module->getOrInsertFunction("FLARE_str_init", f);
        builder->CreateCall(initFun,
                            {builder->CreateLoad(builder->CreateStructGEP(var, 0)),
                             builder->CreateGlobalStringPtr(StringRef(lVal.sVal))});

        builder->CreateStore(ConstantInt::get(*context->getLLVMContext(), APInt(64,
                                                                                strlen(lVal.sVal))),
                             builder->CreateStructGEP(var, 1));
        return var;
    }

    Type *StringType::getLLVMPtrType(Context *context) {
        return nullptr;
    }

    Value *StringType::getDefaultValue(Context *cxt) {
        LValue lValue = {
                .sVal = const_cast<char *>("")
        };
        return this->createInstance(cxt, lValue);
    }

    Value *StringType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *StringType::getValue(Context *cxt, Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *StringType::apply(Context *cxt, OperatorType symbol, Value *primary) {
        return nullptr;
    }
}
