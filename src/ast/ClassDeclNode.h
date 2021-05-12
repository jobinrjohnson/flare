//
// Created by jobinrjohnson on 12/05/21.
//

#ifndef FLARE_CLASSDECLNODE_H
#define FLARE_CLASSDECLNODE_H

#include "Node.h"

namespace ast {

    class ClassDeclNode : public Node {

        std::string className;
        Node *condition;

    public:


        NodeType getNodeType() override;

        explicit ClassDeclNode(const char *name);

        llvm::Value *codeGen(Context *cxt) override;

    };


}

#endif //FLARE_CLASSDECLNODE_H
