//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_BOOLTYPE_H
#define FLARE_BOOLTYPE_H


#include "BaseType.h"

namespace flare::types {

    class BoolType : public BaseType {

    protected:
        Type *probeLLVMType() override;

    public:

        explicit BoolType(Context *cxt) : BaseType(cxt) {};

        inline bool isInbuiltTy() override {
            return true;
        }

        Type *getLLVMPtrType() override;

        Value *createInstance(LValue) override;

        Value *createValue(LValue) override;

        Value *getDefaultValue() override;

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_BOOLEAN;
        }

        ~BoolType() override {
        }

    };

}


#endif //FLARE_BOOLTYPE_H
