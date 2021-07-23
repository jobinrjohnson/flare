//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/ClassObjectType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *ClassObjectType::probeLLVMType(Context *context) {
        return this
                ->classDeclNode
                ->getClassLLVMType();
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

    Type *ClassObjectType::getLLVMPtrType(Context *) {
        return this
                ->classDeclNode
                ->getClassLLVMPointerType();
    }

    Value *ClassObjectType::getDefaultValue(Context *) {
        return nullptr;
    }

    Value *ClassObjectType::getMemberPtr(std::string varName, Value *object) {

        Value *value = object;
        if (value->getType()->isPointerTy() && value->getType()->getPointerElementType()->isPointerTy()) {
            // Probably we should iterate
            value = builder.CreateLoad(value);
        }

        unsigned int index = this->classDeclNode->getVariableIndex(varName);

        auto arrayPtrLoad = builder.CreateStructGEP(
                value, index
        );

        return arrayPtrLoad;
    }

    Value *ClassObjectType::apply(Context *cxt, OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }
}
