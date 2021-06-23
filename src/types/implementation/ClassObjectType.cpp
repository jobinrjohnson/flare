//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/ClassObjectType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *ClassObjectType::probeLLVMType(Context *context) {
        return this
                ->classDeclNode
                ->getClassLLVMPointerType();
    }

    Value *ClassObjectType::createInstance(Context *context, LValue lVal) {

        std::string varName = this->classDeclNode->getQualifiedClassName() + "::object";

        return new AllocaInst(
                this->getLLVMType(context),
                0,
                varName,
                context->getBuilder()->GetInsertBlock()
        );

    }

    ClassObjectType::ClassObjectType(ClassDeclNode *classDeclNode) {
        this->classDeclNode = classDeclNode;
    }
}
