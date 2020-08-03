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

        AssignmentNode(char *name, Node *node) {
            this->varName = name;
            this->expression = node;
        }

        llvm::Value *codeGen() {

            Value *value = this->expression->codeGen();

            auto variable = modules->getGlobalVariable(this->varName);
            builder.CreateStore(value,variable);

            return value;
        }


    };

}


#endif //FLARE_ASSIGNMENTNODE_H
