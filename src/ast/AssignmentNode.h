//
// Created by jobinrjohnson on 8/3/20.
//

#ifndef FLARE_ASSIGNMENTNODE_H
#define FLARE_ASSIGNMENTNODE_H


#include "Node.h"

namespace ast {

    class AssignmentNode : public Node {

    protected:

        std::string varName;
        Node *expression;

    public:

        NodeType getNodeType();

        AssignmentNode(char *name, Node *node);

        llvm::Value *codeGen(int depth);

    };

}


#endif //FLARE_ASSIGNMENTNODE_H
