//
// Created by jobinrjohnson on 7/5/20.
//

#ifndef FLARE_EXPRNODE_H
#define FLARE_EXPRNODE_H

#include "Node.h"

namespace flare::ast {

    class ExprNode : public Node {

    protected:

        std::vector<Node *> operands;
        OperatorType opr;

        Value *codeGenBinaryExpr(Context *cxt);

        Value *codeGenUnaryExpr(Context *cxt);

    public:

        NodeType getNodeType();

        ExprNode(OperatorType opr, Node *a);

        ExprNode(OperatorType opr, Node *a, Node *b);

        llvm::Value *codeGen(Context *cxt);

        Node* getOperandNode();

    };

}

#endif //FLARE_EXPRNODE_H
