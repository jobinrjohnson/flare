//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_INTTYPE_H
#define FLARE_INTTYPE_H

#include "BaseType.h"

namespace flare::types {

    class IntType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

        Value *createValue(Context *, LValue) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *primary) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_INT;
        }

    };

}


#endif //FLARE_INTTYPE_H
