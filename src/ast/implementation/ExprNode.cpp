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


    Value *ExprNode::codeGenBinaryExpr(int depth) {

        llvm::Value *value;
        Value *lhs = this->operands[0]->codeGen(depth + 1);
        Value *rhs = this->operands[1]->codeGen(depth + 1);

        switch (this->opr) {
            // Arithmetic operators
            case PLUS:
                value = builder.CreateAdd(lhs, rhs, "mAdd");
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
                value = builder.CreateICmpSLT(lhs, rhs, "mLt");
                break;
            case GREATER_THAN:
                value = builder.CreateICmpSGT(lhs, rhs, "mGt");
                break;
            case GREATER_THAN_EQUAL:
                value = builder.CreateICmpSGE(lhs, rhs, "mGte");
                break;
            case LESS_THAN_EQUAL:
                value = builder.CreateICmpSLE(lhs, rhs, "mLte");
                break;
            case EQUALITY:
                value = builder.CreateICmpEQ(lhs, rhs, "mEq");
                break;
            case NOT_EQUALITY:
                value = builder.CreateICmpNE(lhs, rhs, "mNeq");
                break;
            default:
                throw "Not handled";
        }
        return value;
    }

    Value *ExprNode::codeGenUnaryExpr(int depth) {

        llvm::Value *value;
        Value *operand = this->operands[0]->codeGen(depth + 1);

        switch (this->opr) {
            case VAR_DE_REF:
            case GROUPED:
            case SCALAR:
            case UNARY_PLUS:
                value = operand;
                break;
            case UNARY_MINUS: {
                this->operands.push_back(new LiteralNode(0));
                value = this->codeGenBinaryExpr(depth);
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


    llvm::Value *ExprNode::codeGen(int depth) {

        this->printCallStack(depth, "ExprNode", __FUNCTION__);

        llvm::Value *value;

        switch (this->opr) {
            case SCALAR:
            case VAR_DE_REF:
            case NOT:
            case GROUPED:
            case UNARY_PLUS:
            case UNARY_MINUS:
                value = this->codeGenUnaryExpr(depth);
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
                value = this->codeGenBinaryExpr(depth);
                break;
            default:
                throw "Operand not implemented."; // TODO throw proper error.
        }

        return value;


    }

}
