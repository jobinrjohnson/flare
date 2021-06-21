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