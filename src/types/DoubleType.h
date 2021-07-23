//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_DOUBLETYPE_H
#define FLARE_DOUBLETYPE_H

#include "BaseType.h"

namespace flare::types {

    class DoubleType : public BaseType {

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

        int getTypePrecedence() override {
            return VariableType::VARTYPE_DOUBLE;
        }

    };

}


#endif //FLARE_DOUBLETYPE_H
