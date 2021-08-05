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

        Type *probeLLVMType(Context *) override;

    public:
        ClassDeclNode *classDeclNode;

        explicit ClassObjectType(ClassDeclNode *classDeclNode);

        inline bool isInbuiltTy() override {
            return false;
        }

        inline unsigned int getVariableIndex(std::string name) {
            return this->classDeclNode->getVariableIndex(name);
        }

        inline std::string getFullyQualifiedName() {
            return this->classDeclNode->getQualifiedClassName();
        }

        Value *createValue(Context *, LValue) override;

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

        Value *getMemberPtr(std::string, Value *);

        Value *apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) override;

        Value *apply(Context *cxt, OperatorType symbol, Value *primary) override;

        Value *getValue(Context *cxt, Value *value, VariableType valueType) override;

        int getTypePrecedence() override {
            return VariableType::VARTYPE_VOID;
        }

    };

}


#endif //FLARE_CLASSOBJECTTYPE_H
