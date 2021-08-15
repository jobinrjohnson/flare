//
// Created by jobinrjohnson on 06/08/21.
//

#ifndef FLARE_ARRAYTYPE_H
#define FLARE_ARRAYTYPE_H


#include "BaseType.h"

namespace flare::types {
    class FArrayType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

        VariableType arrayType;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Value *createValue(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

        Value *apply(Context *cxt, OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *primary) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

        std::string getCFunctionBindingType() {
            switch (this->arrayType) {

                case VARTYPE_BOOLEAN:
                    return "bool";
                case VARTYPE_INT_32:
                    break;
                case VARTYPE_INT_64:
                case VARTYPE_INT:
                    return "int64_t";
                case VARTYPE_FLOAT:
                    break;
                case VARTYPE_DOUBLE:
                case VARTYPE_NUMBER:
                    return "double";
                case VARTYPE_ARRAY:
                    break;
                case VARTYPE_STRING:
                    break;
                case VARTYPE_VOID:
                    break;
                case OTHER:
                    break;
            }

            throw "Type implementation not available";
        }

        void setArrayType(VariableType a) {
            this->arrayType = a;
        }

        int getTypePrecedence() override {
            return VariableType::VARTYPE_ARRAY;
        }

    };
}


#endif //FLARE_ARRAYTYPE_H
