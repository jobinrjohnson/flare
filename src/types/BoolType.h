//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_BOOLTYPE_H
#define FLARE_BOOLTYPE_H


#include "BaseType.h"

namespace flare::types {

    class BoolType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Type *getLLVMPtrType(Context *) override;

        Value *createInstance(Context *, LValue) override;

        Value *getDefaultValue(Context *) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_BOOLEAN;
        }

    };

}


#endif //FLARE_BOOLTYPE_H
