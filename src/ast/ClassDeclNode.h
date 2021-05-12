//
// Created by jobinrjohnson on 12/05/21.
//

#ifndef FLARE_CLASSDECLNODE_H
#define FLARE_CLASSDECLNODE_H

#include "Node.h"
#include "FunctionNode.h"

namespace ast {

    class ClassDeclNode : public Node {

        std::string className;

        std::vector<FunctionNode *> functions;
        std::vector<VarDeclNode *> vars;

    public:


        NodeType getNodeType() override;

        explicit ClassDeclNode(const char *name, std::vector<ast::Node *> *nodeList);

        llvm::Value *codeGen(Context *cxt) override;

    };


}

#endif //FLARE_CLASSDECLNODE_H
