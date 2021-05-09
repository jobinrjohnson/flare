//
// Created by jobinrjohnson on 08/05/21.
//

#ifndef FLARE_FUNCTIONCALLNODE_H
#define FLARE_FUNCTIONCALLNODE_H

#include "Node.h"

namespace ast {
    class FunctionCallNode : public Node {

    protected:
        std::string functionName;

    public:

        explicit FunctionCallNode(std::string functionName);

        NodeType getNodeType() override;

        llvm::Value *codeGen(Context *cxt) override;

    };

}

#endif //FLARE_FUNCTIONCALLNODE_H
