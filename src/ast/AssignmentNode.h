//
// Created by jobinrjohnson on 8/3/20.
//

#ifndef FLARE_ASSIGNMENTNODE_H
#define FLARE_ASSIGNMENTNODE_H


#include "Node.h"

namespace flare::ast {

    class AssignmentNode : public Node {

    public:

        std::string varName;

        std::string base;

        Node *expression;

        Node *index;


        NodeType getNodeType();

        AssignmentNode(char *name, Node *node);

        AssignmentNode(std::string name, std::string base, Node *exprNode);

        AssignmentNode(char *name, Node *indexNode, Node *exprNode);

        llvm::Value *codeGen(Context *cxt);

        llvm::Value *codeGenArrayAssign(Context *cxt);

        llvm::Value *codeGenObjectAssign(Context *cxt);

        ~AssignmentNode() {
            delete (index);
            delete (expression);
        }

    };

}


#endif //FLARE_ASSIGNMENTNODE_H
