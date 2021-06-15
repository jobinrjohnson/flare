//
// Created by jobinrjohnson on 15/06/21.
//

#ifndef FLARE_CFFIINCLUDENODE_H
#define FLARE_CFFIINCLUDENODE_H


#include "Node.h"

namespace flare::ast {
    class CffiIncludeNode : public Node {

    protected:
        std::string name;
        std::string alias;

    public:

        CffiIncludeNode(std::string name, std::string alias);

        NodeType getNodeType() override {
            return NodeType::LITERAL_NODE;
        }

        // Node:codegen override
        llvm::Value *codeGen(Context *cxt) override;


    };
}


#endif //FLARE_CFFIINCLUDENODE_H
