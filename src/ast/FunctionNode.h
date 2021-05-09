//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_FUNCTIONNODE_H
#define FLARE_FUNCTIONNODE_H


#include "Node.h"
#include "StatementListNode.h"

namespace ast {

    class Parameter {
    public:
        std::string name;

        explicit Parameter(std::string name) {
            this->name = name;
        }
    };

    class FunctionNode : public Node {

        StatementListNode *statementListNode;
        std::string name;
        bool hasMultipleExits = false;
        std::vector<ast::Parameter *> *parameterList;

    protected:
        Node *node;

        void prepareBlocks();

    public:

        BasicBlock *entryBlock;
        BasicBlock *exitBlock;
        Function *function;
        AllocaInst *retValue;

        NodeType getNodeType() override;

        explicit FunctionNode(const char *name, StatementListNode *statements);

        explicit FunctionNode(const char *name, StatementListNode *statements,
                              std::vector<ast::Parameter *> *parameterList);

        llvm::FunctionType *codeGenSignature(Context *cxt);

        llvm::Value *codeGen(Context *cxt) override;

        void setHasMultipleExits();

    };
}


#endif //FLARE_FUNCTIONNODE_H
