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
    VAR_DE_REF,
    GREATER_THAN,
    LESS_THAN,
    EQUALITY
};

namespace ast {
    class ExprNode : public Node {

    private:

        std::vector<Node *> operands;
        OperatorType opr;

    public:

        NodeType getNodeType();

        ExprNode(OperatorType opr, Node *a);

        ExprNode(OperatorType opr, Node *a, Node *b);

        llvm::Value *codeGen(int depth);

    };

}

#endif //FLARE_EXPRNODE_H
