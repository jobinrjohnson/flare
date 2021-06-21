//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_CLASSOBJECTTYPE_H
#define FLARE_CLASSOBJECTTYPE_H

#include <ast/ClassDeclNode.h>
#include "BaseType.h"

namespace flare::types {

    class ClassObjectType : public BaseType {

        ClassDeclNode *classDeclNode;

    public:

        explicit ClassObjectType(ClassDeclNode *classDeclNode);

        Type *getLLVMType(Context *) override;

        inline bool isInbuiltTy() {
            return false;
        }

        Value *createInstance(Context *, LValue) override;

    };

}


#endif //FLARE_CLASSOBJECTTYPE_H
