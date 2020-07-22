//
// Created by jobinrjohnson on 7/5/20.
//

#include "ExprNode.h"
#include "LiteralNode.h"

namespace ast {
    ExprNode::ExprNode() {

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

    ExprNode::ExprNode(OperatorType opr, Node *a, Node *b, Node *c) {
        this->opr = opr;
        this->operands.push_back(a);
        this->operands.push_back(b);
        this->operands.push_back(c);
    }

    llvm::Value *ExprNode::codeGen() {

        llvm::Value *value;

        switch (this->opr) {
            case PLUS:
                value = builder.CreateAdd(
                        this->operands[0]->codeGen(), this->operands[1]->codeGen(),
                        "add");
                break;
            case MINUS:
                value = builder.CreateFSub(
                        this->operands[0]->codeGen(), this->operands[1]->codeGen(),
                        "sub");
                break;
            default:
                throw "Operand not implemented."; // TODO throw proper error.
        }

        return value;


    }

}