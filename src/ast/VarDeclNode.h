//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_VARDECLNODE_H
#define FLARE_VARDECLNODE_H


#include "Node.h"
#include "LiteralNode.h"

namespace ast {

    class VarDeclNode : public Node {

    protected:
        std::string variableName;
        Node *initialValue;
        bool isArray = false;

    public:

        NodeType getNodeType();

        VarDeclNode(char *name);

        VarDeclNode(char *name, bool isArray);

        VarDeclNode(char *name, Node *initialValue, bool isArray = false);

        void setInitializer(Node *initial);

        Value *codeGenArray();

        Value *codeGenBuiltInTy(Context *);

        llvm::Value *codeGen(Context *cxt);

    };

}

#endif //FLARE_VARDECLNODE_H
