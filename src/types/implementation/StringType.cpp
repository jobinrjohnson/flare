//
// Created by jobinrjohnson on 19/06/21.
//

#include "types/StringType.h"
#include <ast/helpers/Context.h>

namespace flare::types {
    Type *StringType::probeLLVMType() {
        std::vector<llvm::Type *> items = {
                this->cxt->getBuilder()->getInt8PtrTy()
        };
        auto stringLLVMType = StructType::create(*this->cxt->getLLVMContext(), items, "FLARE_string_t");
        return PointerType::get(stringLLVMType, 0);
    }


    Value *StringType::createValue(LValue val) {
        return this->createInstance(val);
    }

    Value *StringType::createInstance(LValue lVal) {

        auto builder = this->cxt->getBuilder();
        auto var = builder->CreateAlloca(this->getLLVMType());
        this->createCall("FLARE_str_init", builder->getVoidTy(),
                         {PointerType::get(this->getLLVMType(), 0), builder->getInt8PtrTy()},
                         {var, this->cxt->getBuilder()->CreateGlobalStringPtr(StringRef(lVal.sVal))});
        // TODO freeup allocated mem on out of scope
        return var;
    }

    Type *StringType::getLLVMPtrType() {
        return nullptr;
    }

    Value *StringType::getDefaultValue() {
        LValue lValue = {
                .sVal = const_cast<char *>("")
        };
        return this->createInstance(lValue);
    }

    Value *StringType::apply(OperatorType symbol, Value *lhs) {
        return nullptr;
    }

    Value *StringType::getValue(Value *value, VariableType valueType) {


        if (value->getType()->isPointerTy() && value->getType()->getPointerElementType() == this->getLLVMType()) {
            return cxt->getBuilder()->CreateLoad(value);
        }

        return value;
    }

    Value *StringType::apply(OperatorType symbol, Value *primary, Value *secondary) {

        Value *lhs = primary;
        auto rhs = cxt->getFlareType(secondary)->getValue(secondary, VariableType::VARTYPE_STRING);

        // TODO refactor
        while (lhs->getType()->isPointerTy()) {
            if (lhs->getType() == this->getLLVMType()) {
                break;
            }
            lhs = builder.CreateLoad(lhs);
        }
        while (rhs->getType()->isPointerTy()) {
            if (rhs->getType() == this->getLLVMType()) {
                break;;
            }
            rhs = builder.CreateLoad(rhs);
        }

        auto builder = cxt->getBuilder();

        switch (symbol) {
            case ASSIGNMENT:
                this->createCall("FLARE_str_assign", builder->getVoidTy(),
                                 {this->getLLVMType(), this->getLLVMType()}, {lhs, rhs});
                return lhs;
            case OperatorType::PLUS : {
                auto res = this->getDefaultValue();
                res->setName("cRes");
                this->createCall("FLARE_str_concat", builder->getVoidTy(),
                                 {this->getLLVMType(), this->getLLVMType(),
                                  PointerType::get(this->getLLVMType(), 0)},
                                 {lhs, rhs, res});
                return builder->CreateLoad(res);
            }
            case OperatorType::EQUALITY :
                return this->createCall("FLARE_str_is_equal", builder->getInt1Ty(),
                                        {this->getLLVMType(), this->getLLVMType()}, {lhs, rhs});
            case OperatorType::NOT_EQUALITY : {
                auto res = this->apply(OperatorType::EQUALITY, primary, secondary);
                return builder->CreateNot(res);
            }
            default:
                throw "Operator not supported on string operand";
        }

    }

    Value *StringType::apply(OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }

}
