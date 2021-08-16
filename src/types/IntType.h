//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_INTTYPE_H
#define FLARE_INTTYPE_H

#include "BaseType.h"

namespace flare::types {

    class IntType : public BaseType {

    protected:
        Type *probeLLVMType() override;

    public:

        explicit IntType(Context *cxt) : BaseType(cxt) {};

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(LValue) override;

        Type *getLLVMPtrType() override;

        Value *getDefaultValue() override;

        Value *createValue(LValue) override;

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_INT;
        }

        ~IntType() override {
        }

    };

}


#endif //FLARE_INTTYPE_H
