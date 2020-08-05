//
// Created by jobinrjohnson on 7/5/20.
//

#include "ExprNode.h"

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
        std::cout << "Calling ExprNode@codegen" << "\n";

        llvm::Value *value;

        switch (this->opr) {
            case SCALAR:
                return this->operands[0]->codeGen();
                break;
            case VAR_DE_REF:
                return this->operands[0]->codeGen();
                break;
            case PLUS:
                value = builder.CreateAdd(
                        this->operands[0]->codeGen(),
                        this->operands[1]->codeGen(),
                        "mAdd"
                );
                break;
            case MINUS:
                value = builder.CreateSub(
                        this->operands[0]->codeGen(),
                        this->operands[1]->codeGen(),
                        "mSub"
                );
                break;
            case MUL:
                value = builder.CreateMul(
                        this->operands[0]->codeGen(),
                        this->operands[1]->codeGen(),
                        "mMul"
                );
                break;
            case DIV:
                value = builder.CreateFDiv(
                        this->operands[0]->codeGen(),
                        this->operands[1]->codeGen(),
                        "mDiv"
                );
                break;
            default:
                throw "Operand not implemented."; // TODO throw proper error.
        }

        return value;


    }

}