//
// Created by jobinrjohnson on 8/9/20.
//

#ifndef FLARE_LOGSMTNODE_H
#define FLARE_LOGSMTNODE_H


#include "Node.h"

namespace flare::ast {
    class LogSmtNode : public Node {

    protected:
        Node *node;

    public:

        NodeType getNodeType();

        LogSmtNode(Node *exprNode);

        llvm::Value *codeGen(Context *cxt);

    };

}

#endif //FLARE_LOGSMTNODE_H
