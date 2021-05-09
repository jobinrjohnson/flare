//
// Created by jobinrjohnson on 08/05/21.
//

#ifndef FLARE_FUNCTIONCALLNODE_H
#define FLARE_FUNCTIONCALLNODE_H

#include "Node.h"
#include "ExprNode.h"

namespace ast {
    class FunctionCallNode : public Node {

    protected:
        std::string functionName;
        std::vector<ExprNode *> *argumentList;

    public:

        explicit FunctionCallNode(std::string functionName);

        explicit FunctionCallNode(std::string functionName, std::vector<ExprNode *> *argumentList);

        NodeType getNodeType() override;

        llvm::Value *codeGen(Context *cxt) override;

    };

}

#endif //FLARE_FUNCTIONCALLNODE_H
