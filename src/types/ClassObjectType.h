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

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

    };

}


#endif //FLARE_CLASSOBJECTTYPE_H
