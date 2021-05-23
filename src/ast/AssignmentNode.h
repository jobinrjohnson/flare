//
// Created by jobinrjohnson on 8/3/20.
//

#ifndef FLARE_ASSIGNMENTNODE_H
#define FLARE_ASSIGNMENTNODE_H


#include "Node.h"

namespace flare::ast {

    class AssignmentNode : public Node {

    protected:

        std::string varName;

        Node *expression;

        Node *index;

    public:

        NodeType getNodeType();

        AssignmentNode(char *name, Node *node);

        AssignmentNode(char *name, Node *indexNode, Node *exprNode);

        llvm::Value *codeGen(Context *cxt);

    };

}


#endif //FLARE_ASSIGNMENTNODE_H
