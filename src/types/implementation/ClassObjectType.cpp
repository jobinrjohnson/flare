//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/ClassObjectType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *ClassObjectType::getLLVMType(Context *context) {
        return this
                ->classDeclNode
                ->getClassLLVMPointerType();
    }

    Value *ClassObjectType::createInstance(Context *context, LValue lVal) {
        return nullptr;
    }

    ClassObjectType::ClassObjectType(ClassDeclNode *classDeclNode) {
        this->classDeclNode = classDeclNode;
    }
}
