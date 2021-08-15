//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_STRINGTYPE_H
#define FLARE_STRINGTYPE_H

#include "BaseType.h"

namespace flare::types {


    class StringType : public BaseType {

    protected:
        Type *probeLLVMType() override;

    public:


        explicit StringType(Context *cxt) : BaseType(cxt) {};

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(LValue) override;

        Value *createValue(LValue val) override;

        Type *getLLVMPtrType() override;

        Value *getDefaultValue() override;

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_STRING;
        }

    };

}


#endif //FLARE_STRINGTYPE_H
