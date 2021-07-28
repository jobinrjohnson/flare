//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/StringType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Type *StringType::probeLLVMType(Context *context) {
        std::vector<llvm::Type *> items = {
                context->getBuilder()->getInt8PtrTy()
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
                // TODO free the first instance fix memcopy
                return builder->CreateStore(rhs, lhs);
            }
            case OperatorType::PLUS :
                this->createCall(cxt, "FLARE_str_concat", builder->getVoidTy(),
                                 {this->getLLVMType(cxt), this->getLLVMType(cxt)}, {lhs, rhs});
                return lhs;
            case OperatorType::EQUALITY :
                return this->createCall(cxt, "FLARE_str_is_equal", builder->getInt1Ty(),
                                        {this->getLLVMType(cxt), this->getLLVMType(cxt)}, {lhs, rhs});
            case OperatorType::NOT_EQUALITY : {
                auto res = this->apply(cxt, OperatorType::EQUALITY, primary, secondary);
                return builder->CreateNot(res);
            }
            default:
                throw "Operator not supported on string operand";
        }

    }
}
