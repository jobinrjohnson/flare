//
// Created by jobinrjohnson on 9/23/20.
//

#ifndef FLARE_STATEMENTNODE_H
#define FLARE_STATEMENTNODE_H

#include "Node.h"

namespace ast {

    enum StatementType {
        RETURN
    };

    class StatementNode : public Node {

    protected:
        std::vector<Node *> operands;
        StatementType type;

    public:

        NodeType getNodeType() {
            return STATEMENT_NODE;
        }

        explicit StatementNode(StatementType type, Node *node);

        llvm::Value *codeGen(Context *cxt);

    };

}


#endif //FLARE_STATEMENTNODE_H
