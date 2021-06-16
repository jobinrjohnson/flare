//
// Created by jobinrjohnson on 7/5/20.
//

#ifndef FLARE_EXPRNODE_H
#define FLARE_EXPRNODE_H

#include "Node.h"

namespace flare::ast {


    enum OperatorType {
        PLUS,
        MINUS,
        MUL,
        DIV,
        SCALAR,
        VAR_DE_REF,
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_EQUAL,
        LESS_THAN_EQUAL,
        EQUALITY,
        NOT_EQUALITY,
        NOT,
        GROUPED,
        UNARY_PLUS,
        UNARY_MINUS,
        MODULO_DIV,
        FUNCTION_CALL,
    };

    class ExprNode : public Node {

    protected:

        std::vector<Node *> operands;
        OperatorType opr;

        Value *codeGenBinaryExpr(Context *cxt);

        Value *codeGenUnaryExpr(Context *cxt);

        Value *codeGenFloatingPointBinaryExpr(Context *cxt, Value *lhs, Value *rhs);

        Value *codeGenIntegerBinaryExpr(Context *cxt, Value *lhs, Value *rhs);

    public:

        NodeType getNodeType();

        ExprNode(OperatorType opr, Node *a);

        ExprNode(OperatorType opr, Node *a, Node *b);

        llvm::Value *codeGen(Context *cxt);

        Node* getOperandNode();

    };

}

#endif //FLARE_EXPRNODE_H
