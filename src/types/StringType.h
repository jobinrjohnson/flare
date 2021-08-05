//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_STRINGTYPE_H
#define FLARE_STRINGTYPE_H

#include "BaseType.h"

namespace flare::types {


    class StringType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Value *createValue(Context *context, LValue val) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *primary) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_STRING;
        }

    };

}


#endif //FLARE_STRINGTYPE_H
