//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_CLASSOBJECTTYPE_H
#define FLARE_CLASSOBJECTTYPE_H

#include <ast/ClassDeclNode.h>
#include "BaseType.h"

namespace flare::types {

    class ClassObjectType : public BaseType {


    protected:

        Type *probeLLVMType() override;

    public:
        ClassDeclNode *classDeclNode;

        explicit ClassObjectType(Context *cxt, ClassDeclNode *classDeclNode);

        inline bool isInbuiltTy() override {
            return false;
        }

        inline unsigned int getVariableIndex(std::string name) {
            return this->classDeclNode->getVariableIndex(name);
        }

        inline std::string getFullyQualifiedName() {
            return this->classDeclNode->getQualifiedClassName();
        }

        Value *createValue(LValue) override;

        Value *createInstance(LValue) override;

        Type *getLLVMPtrType() override;

        Value *getDefaultValue() override;

        Value *getMemberPtr(std::string, Value *);

        Value *apply(OperatorType symbol, std::vector<Value *> operands) override;

        Value *apply(OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(OperatorType symbol, Value *primary) override;

        Value *getValue(Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_VOID;
        }

        ~ClassObjectType() override {
            delete this->classDeclNode;
        }

    };

}


#endif //FLARE_CLASSOBJECTTYPE_H
