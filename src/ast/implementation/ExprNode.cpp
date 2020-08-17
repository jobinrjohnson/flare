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

        std::cout << rhs->getType()->getTypeID() << "]]]][[[[" << lhs->getType()->getTypeID() << "\n\n\n";

        if (rhs->getType()->getTypeID() != lhs->getType()->getTypeID()) {

            if (rhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                lhs = builder.CreateSIToFP(lhs, Type::getDoubleTy(context), "convertedFl");
            }
            if (lhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                rhs = builder.CreateSIToFP(rhs, Type::getDoubleTy(context), "convertedFl");
            }

        }


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
                if (lhs->getType()->getTypeID() == llvm::Type::DoubleTyID) {
                    value = builder.CreateFCmpOLT(lhs, rhs, "mAdd");
                } else {
                    value = builder.CreateICmpSLT(lhs, rhs, "mAdd");
                };
                break;
            case GREATER_THAN: // TODO remaining
                return builder.CreateICmpSGT(lhs, rhs, "mGt");
            case GREATER_THAN_EQUAL:
                return builder.CreateICmpSGE(lhs, rhs, "mGte");
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
