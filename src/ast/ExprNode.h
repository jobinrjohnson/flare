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
        ExprNode();

        ExprNode(OperatorType opr, Node *a); // unary
        ExprNode(OperatorType opr, Node *a, Node *b); // binary
        ExprNode(OperatorType opr, Node *a, Node *b, Node *c); // ternary

        llvm::Value *codeGen();

    };

}

#endif //FLARE_EXPRNODE_H
