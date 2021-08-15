//
// Created by jobinrjohnson on 21/06/21.
//

#include "types/ClassObjectType.h"
#include <ast/helpers/Context.h>

namespace flare::types {

    Type *ClassObjectType::probeLLVMType() {
        return this
                ->classDeclNode
                ->getClassLLVMType();
    }

    Value *ClassObjectType::createInstance(LValue lVal) {

        std::string varName = this->classDeclNode->getQualifiedClassName() + "::object";

        return new AllocaInst(
                this->getLLVMType(),
                0,
                varName,
                this->cxt->getBuilder()->GetInsertBlock()
        );

    }


    Value *ClassObjectType::createValue(LValue val) {
        return nullptr;
    }


    ClassObjectType::ClassObjectType(Context *cx, ClassDeclNode *classDeclNode) : BaseType(cx) {
        this->classDeclNode = classDeclNode;
    }

    Type *ClassObjectType::getLLVMPtrType() {
        return this
                ->classDeclNode
                ->getClassLLVMPointerType();
    }

    Value *ClassObjectType::getDefaultValue() {
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

    Value *ClassObjectType::apply(OperatorType symbol, Value *lhs, Value *rhs) {
        return nullptr;
    }

    Value *ClassObjectType::getValue(Value *value, VariableType valueType) {
        return nullptr;
    }

    Value *ClassObjectType::apply(OperatorType symbol, Value *primary) {
        return nullptr;
    }

    Value *ClassObjectType::apply(OperatorType symbol, std::vector<Value *> operands) {
        return nullptr;
    }
}
