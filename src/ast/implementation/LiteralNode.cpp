//
// Created by jobinrjohnson on 7/22/20.
//

#include <ast/LiteralNode.h>
#include <exceptions/UnimplementedException.h>
#include <types/BaseType.h>

namespace flare::ast {

    LiteralNode::LiteralNode(int mLiteralValue) {
        this->nodeValue.iVal = mLiteralValue;
        this->literalType = VariableType::VARTYPE_INT;
    }

    LiteralNode::LiteralNode(double mLiteralValue) {
        this->nodeValue.dVal = mLiteralValue;
        this->literalType = VariableType::VARTYPE_DOUBLE;
    }

    LiteralNode::LiteralNode(bool mLiteralValue) {
        this->nodeValue.bVal = mLiteralValue;
        this->literalType = VariableType::VARTYPE_BOOLEAN;
    }

    llvm::Value *LiteralNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "LiteralNode", __FUNCTION__);

        types::BaseType *fType = cxt->getFlareType(this->literalType);
        return fType->createInstance(cxt, this->nodeValue);

        switch (this->literalType) {

            case VariableType::VARTYPE_INT_32:
                return llvm::ConstantInt::get(context, APInt(32, this->nodeValue.iVal));
            case VariableType::VARTYPE_INT_64:
            case VariableType::VARTYPE_INT:
                return llvm::ConstantInt::get(context, APInt(64, this->nodeValue.iVal));
            case VariableType::VARTYPE_BOOLEAN:
                return ConstantInt::get(context, APInt(1, this->nodeValue.bVal));
            case VariableType::VARTYPE_FLOAT:
                return ConstantFP::get(Type::getFloatTy(context), this->nodeValue.dVal);
            case VariableType::VARTYPE_DOUBLE:
            case VariableType::VARTYPE_NUMBER:
                return ConstantFP::get(Type::getDoubleTy(context), this->nodeValue.dVal);
            case VariableType::VARTYPE_STRING:
                return builder.CreateGlobalStringPtr(StringRef(this->nodeValue.sVal), "str");
            case VariableType::VARTYPE_ARRAY:
            case VariableType::VARTYPE_VOID:
            case VariableType::VARTYPE_OBJECT:
            case VariableType::OTHER:
                break;
        }
        throw new exceptions::UnimplementedException("Literal array and other not implemented");

    }

    LiteralNode::LiteralNode(char *mLiteralValue) {
        // TODO process string for escape sequence;
        this->nodeValue.sVal = mLiteralValue;
        this->literalType = VariableType::VARTYPE_STRING;
    }

    VariableType LiteralNode::getVarType() {
        return this->literalType;
    }

}