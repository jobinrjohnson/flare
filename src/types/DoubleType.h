//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_DOUBLETYPE_H
#define FLARE_DOUBLETYPE_H

#include "BaseType.h"

namespace flare::types {

    class DoubleType : public BaseType {

    protected:
        Type *probeLLVMType() override;

    public:


        explicit DoubleType(Context *cxt) : BaseType(cxt) {};

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(LValue) override;

        Value *createValue(LValue) override;

        Type *getLLVMPtrType() override;

        Value *getDefaultValue() override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_DOUBLE;
        }


        ~DoubleType() override {
        }

    };

}


#endif //FLARE_DOUBLETYPE_H
