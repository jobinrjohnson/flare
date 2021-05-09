//
// Created by jobinrjohnson on 7/5/20.
//

#include <LiteralNode.h>
#include "ExprNode.h"

namespace ast {

    NodeType ExprNode::getNodeType() {
        return EXPR_NODE;
    }

    ExprNode::ExprNode(OperatorType opr, Node *a) {
        this->opr = opr;
        this->operands.push_back(a);
    }

    ExprNode::ExprNode(OperatorType opr, Node *a, Node *b) {
        this->opr = opr;
        this->operands.push_back(a);
        this->operands.push_back(b);
    }

    Value *ExprNode::codeGenFloatingPointBinaryExpr(Context *cxt, Value *lhs, Value *rhs) {

        llvm::Value *value;
        switch (this->opr) {
            // Arithmetic operators
            case PLUS:
                value = builder.CreateFAdd(lhs, rhs, "mAdd");
                break;
            case MINUS:
                value = builder.CreateFSub(lhs, rhs, "mSub");
                break;
            case MUL:
                value = builder.CreateFMul(lhs, rhs, "mMul");
                break;
            case MODULO_DIV:
                throw "this cant happen";
                break;
            case DIV:
                value = builder.CreateFDiv(lhs, rhs, "mDiv");
                break;
            case UNARY_MINUS:
                value = builder.CreateFSub(rhs, lhs, "mUmin");
                break;
                // Boolean operators
            case LESS_THAN:
                value = builder.CreateFCmpOLT(lhs, rhs, "mAdd");
                break;
            case GREATER_THAN: // TODO remaining
                return builder.CreateFCmpOGT(lhs, rhs, "mGt");
            case GREATER_THAN_EQUAL:
                value = builder.CreateFCmpOGE(lhs, rhs, "mGte");
                break;
            case LESS_THAN_EQUAL:
                return builder.CreateFCmpOLE(lhs, rhs, "mLte");
            case EQUALITY:
                return builder.CreateFCmpOEQ(lhs, rhs, "mEq");
            case NOT_EQUALITY:
                return builder.CreateFCmpONE(lhs, rhs, "mNeq");
            default:
                throw "Not handled";
        }
        return value;
    }


    Value *ExprNode::codeGenIntegerBinaryExpr(Context *cxt, Value *lhs, Value *rhs) {

        llvm::Value *value;

        switch (this->opr) {
            // Arithmetic operators
            case PLUS:
                if (lhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                    value = builder.CreateFAdd(lhs, rhs, "mAdd");
                } else {
                    value = builder.CreateAdd(lhs, rhs, "mAdd");
                };
                break;
            case MINUS:
                value = builder.CreateSub(lhs, rhs, "mSub");
                break;
            case MUL:
                value = builder.CreateMul(lhs, rhs, "mMul");
                break;
            case MODULO_DIV:
                value = builder.CreateSRem(lhs, rhs, "mMod");
                break;
            case DIV:
                value = builder.CreateFDiv(lhs, rhs, "mDiv");
                break;
            case UNARY_MINUS:
                value = builder.CreateSub(rhs, lhs, "mUmin");
                break;
                // Boolean operators
            case LESS_THAN:
                value = builder.CreateICmpSLT(lhs, rhs, "mAdd");
                break;
            case GREATER_THAN: // TODO remaining
                return builder.CreateICmpSGT(lhs, rhs, "mGt");
            case GREATER_THAN_EQUAL:
                value = builder.CreateICmpSGE(lhs, rhs, "mGte");
                break;
            case LESS_THAN_EQUAL:
                return builder.CreateICmpSLE(lhs, rhs, "mLte");
            case EQUALITY:
                return builder.CreateICmpEQ(lhs, rhs, "mEq");
            case NOT_EQUALITY:
                return builder.CreateICmpNE(lhs, rhs, "mNeq");
            default:
                throw "Not handled";
        }
        return value;
    }


    Value *ExprNode::codeGenBinaryExpr(Context *cxt) {

        Value *lhs = this->operands[0]->codeGen(cxt->nextLevel());
        Value *rhs = this->operands[1]->codeGen(cxt->nextLevel());

        if (rhs->getType()->getTypeID() != lhs->getType()->getTypeID()) {

            if (rhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                lhs = builder.CreateSIToFP(lhs, Type::getDoubleTy(context), "convertedFl");
            } else if (lhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                rhs = builder.CreateSIToFP(rhs, Type::getDoubleTy(context), "convertedFl");
            }

            return this->codeGenFloatingPointBinaryExpr(cxt, lhs, rhs);
        }

        return this->codeGenIntegerBinaryExpr(cxt, lhs, rhs);
    }

    Value *ExprNode::codeGenUnaryExpr(Context *cxt) {

        llvm::Value *value;
        Value *operand = this->operands[0]->codeGen(cxt->nextLevel());

        switch (this->opr) {
            case VAR_DE_REF:
            case GROUPED:
            case SCALAR:
            case UNARY_PLUS:
            case FUNCTION_CALL:
                value = operand;
                break;
            case UNARY_MINUS: {
                this->operands.push_back(new LiteralNode(0));
                value = this->codeGenBinaryExpr(cxt);
                break;
            }
            case NOT:
                value = builder.CreateNot(operand, "mNot");
                break;
            default:
                throw "Not handled";
        }
        return value;
    }


    llvm::Value *ExprNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "ExprNode", __FUNCTION__);

        llvm::Value *value;

        switch (this->opr) {
            case SCALAR:
            case VAR_DE_REF:
            case NOT:
            case GROUPED:
            case UNARY_PLUS:
            case UNARY_MINUS:
            case FUNCTION_CALL:
                value = this->codeGenUnaryExpr(cxt);
                break;
            case PLUS:
            case MINUS:
            case MUL:
            case LESS_THAN:
            case LESS_THAN_EQUAL:
            case GREATER_THAN:
            case GREATER_THAN_EQUAL:
            case EQUALITY:
            case NOT_EQUALITY:
            case DIV:
            case MODULO_DIV:
                value = this->codeGenBinaryExpr(cxt);
                break;
            default:
                throw "Operand not implemented."; // TODO throw proper error.
        }

        return value;


    }

}
