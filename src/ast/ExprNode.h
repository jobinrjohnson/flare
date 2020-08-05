//
// Created by jobinrjohnson on 7/5/20.
//

#ifndef FLARE_EXPRNODE_H
#define FLARE_EXPRNODE_H

#include "Node.h"

enum OperatorType {
    PLUS,
    MINUS,
    MUL,
    DIV,
    MODE,
    SCALAR,
    VAR_DE_REF
};

namespace ast {
    class ExprNode : public Node {

    private:
        std::vector<Node *> operands;
        OperatorType opr;

    public:

        NodeType getNodeType() {
            return EXPR_NODE;
        }

        ExprNode(OperatorType opr, Node *a) {
            this->opr = opr;
            this->operands.push_back(a);
        }

        ExprNode(OperatorType opr, Node *a, Node *b) {
            this->opr = opr;
            this->operands.push_back(a);
            this->operands.push_back(b);
        }

        llvm::Value *codeGen() {
            std::cout << "Calling ExprNode@codegen" << "\n";

            llvm::Value *value;

            switch (this->opr) {
                case SCALAR:
                    return this->operands[0]->codeGen();
                case VAR_DE_REF:
                    return this->operands[0]->codeGen();
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

    };

}

#endif //FLARE_EXPRNODE_H
