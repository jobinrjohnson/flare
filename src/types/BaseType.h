//
// Created by jobinrjohnson on 18/06/21.
//

#ifndef FLARE_BASETYPE_H
#define FLARE_BASETYPE_H

#include <llvm/IR/IRBuilder.h>
#include <ast/constants/AstConstants.h>

using namespace llvm;
using namespace flare::ast;

namespace flare::ast {
    class Context;
}

namespace flare::types {

    class BaseType {

    protected:

        Context *cxt;

        Type *type;

        int typeLevel = 0;

        virtual Type *probeLLVMType() = 0;

        Value *createCall(std::string name, Type *returnType, ArrayRef<Type *> paramTypes,
                          ArrayRef<Value *> args, bool isVarArg = false);

    public:

        BaseType(Context *c) {
            this->cxt = c;
        }

//        void setContext() {
//            this->cxt = c;
//        }

        inline Type *getLLVMType() {
            if (this->type == nullptr) {
                this->type = this->probeLLVMType();
            }
            return type;
        }


        virtual Value *getDefaultValue() = 0;

        virtual Value *createValue(LValue) = 0;

        virtual Type *getLLVMPtrType() = 0;

        virtual inline bool isInbuiltTy() = 0;

        virtual Value *createInstance(LValue) = 0;

        virtual Value *apply(OperatorType symbol, std::vector<Value *> operands) = 0;

        virtual Value *apply(OperatorType symbol, Value *lhs, Value *rhs) = 0;

        virtual Value *apply(OperatorType symbol, Value *primary) = 0;

        virtual Value *getValue(Value *value, VariableType valueType) = 0;

        virtual int getTypePrecedence() = 0;

    };

}

#endif //FLARE_BASETYPE_H
