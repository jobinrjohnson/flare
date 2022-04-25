//
// Created by jobinrjohnson on 7/5/20.
//

#include <ast/constants/AstConstants.h>
#include <ast/LiteralNode.h>
#include <ast/ExprNode.h>

namespace flare::ast {

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

    Value *ExprNode::codeGenBinaryExpr(Context *cxt) {
        this->printCallStack(cxt, "ExprNode", __FUNCTION__);

        std::vector<Value *> ops = {
                this->operands[0]->codeGen(cxt->next()), // LHS
                this->operands[1]->codeGen(cxt->next()) // RHS
        };

        auto fType1 = cxt->getFlareType(ops.at(0));
        auto fType2 = cxt->getFlareType(ops.at(1));

        if (fType1->getTypePrecedence() >= fType2->getTypePrecedence()) {
            return fType1->apply(this->opr, ops[0], ops[1]);
        } else {
            return fType2->apply(this->opr, ops[1], ops[0]);
        }

    }

    Value *ExprNode::codeGenUnaryExpr(Context *cxt) {
        this->printCallStack(cxt, "ExprNode", __FUNCTION__);

        llvm::Value *value;
        Value *operand = this->operands[0]->codeGen(cxt->next());

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
                value = cxt->getFlareType(operand)->apply(OperatorType::NOT, operand);
                break;
            default:
                throw "Not handled";
        }
        return value;
    }


    llvm::Value *ExprNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "ExprNode", __FUNCTION__);

        if (this->operands.size() == 1) {
            if (this->opr == PLUS)
                this->opr = UNARY_PLUS;
            if (this->opr == MINUS)
                this->opr = UNARY_MINUS;
        }

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
            case LOGICAL_AND:
            case LOGICAL_OR:
                value = this->codeGenBinaryExpr(cxt);
                break;
            default:
                throw "Operand not implemented."; // TODO throw proper error.
        }

        return value;


    }

    Node *ExprNode::getOperandNode() {
        switch (this->opr) {
            case VAR_DE_REF:
            case GROUPED:
            case SCALAR:
            case UNARY_PLUS:
            case UNARY_MINUS:
            case FUNCTION_CALL:
                break;
            default:
                return nullptr;
        }

        if (auto *x = dynamic_cast<ExprNode *>(this->operands[0])) {
            return x->getOperandNode();
        }

        return this->operands[0];

    }

}
