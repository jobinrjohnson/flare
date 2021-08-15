//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_VOIDTYPE_H
#define FLARE_VOIDTYPE_H

#include "BaseType.h"

namespace flare::types {

    class VoidType : public BaseType {

    protected:
        Type *probeLLVMType() override;

    public:

        explicit VoidType(Context *cxt) : BaseType(cxt) {};

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(LValue) override;

        Type *getLLVMPtrType() override;

        Value *getDefaultValue() override;

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_VOID;
        }

        Value *createValue(LValue val) override;
    };

}

#endif //FLARE_VOIDTYPE_H
