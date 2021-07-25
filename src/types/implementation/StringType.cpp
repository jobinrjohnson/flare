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
        return PointerType::get(stringLLVMType, 0);
    }

    Value *StringType::createInstance(Context *context, LValue lVal) {

        auto builder = context
                ->getBuilder();

        auto var = builder->CreateAlloca(this->getLLVMType(context));

        auto *f = FunctionType::get(
                builder->getVoidTy(),
                {PointerType::get(this->getLLVMType(context), 0), builder->getInt8PtrTy()},
                false
        );
        auto initFun = module->getOrInsertFunction("FLARE_str_init", f);
        builder->CreateCall(
                initFun,
                {
                        var,
                        builder->CreateGlobalStringPtr(StringRef(lVal.sVal))
                }
        );
        return builder->CreateLoad(var);
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

    Value *StringType::apply(Context *cxt, OperatorType symbol, Value *lhs) {
        return nullptr;
    }

    Value *StringType::getValue(Context *cxt, Value *value, VariableType valueType) {
        return value;
    }

    Value *StringType::apply(Context *cxt, OperatorType symbol, Value *primary, Value *secondary) {

        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(cxt, secondary, VariableType::VARTYPE_STRING);

        auto builder = cxt->getBuilder();

        switch (symbol) {
            case ASSIGNMENT: {
                // TODO free the first instance
                return builder->CreateStore(rhs, lhs);
            }
            case OperatorType::PLUS : {
                auto *f = FunctionType::get(
                        builder->getVoidTy(),
                        {this->getLLVMType(cxt), this->getLLVMType(cxt)},
                        false
                );
                auto initFun = module->getOrInsertFunction("FLARE_str_concat", f);
                builder->CreateCall(initFun, {lhs, rhs});
                return lhs;
            }
            default:
                throw "Operator not supported on string operand";
        }

    }
}
