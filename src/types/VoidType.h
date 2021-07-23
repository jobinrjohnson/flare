//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_VOIDTYPE_H
#define FLARE_VOIDTYPE_H

#include "BaseType.h"

namespace flare::types {

    class VoidType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

    };

}

#endif //FLARE_VOIDTYPE_H
