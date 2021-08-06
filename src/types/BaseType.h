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

        Type *type;

        int typeLevel = 0;

        virtual Type *probeLLVMType(Context *) = 0;

        Value *createCall(Context *cxt, std::string name, Type *returnType, ArrayRef<Type *> paramTypes,
                          ArrayRef<Value *> args, bool isVarArg = false);

    public:

        inline Type *getLLVMType(Context *cxt) {
            if (this->type == nullptr) {
                this->type = this->probeLLVMType(cxt);
            }
            return type;
        }


        virtual Value *getDefaultValue(Context *) = 0;

        virtual Value *createValue(Context *, LValue) = 0;

        virtual Type *getLLVMPtrType(Context *) = 0;

        virtual inline bool isInbuiltTy() = 0;

        virtual Value *createInstance(Context *, LValue) = 0;

        virtual Value *apply(Context *cxt, OperatorType symbol, std::vector<Value *> operands) = 0;

        virtual Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) = 0;

        virtual Value *apply(Context *cxt, OperatorType symbol, Value *primary) = 0;

        virtual Value *getValue(Context *cxt, Value *value, VariableType valueType) = 0;

        virtual int getTypePrecedence() = 0;

    };

}

#endif //FLARE_BASETYPE_H
