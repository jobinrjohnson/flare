//
// Created by jobinrjohnson on 7/23/20.
//

#include "StatementListNode.h"

namespace ast {


    NodeType StatementListNode::getNodeType() {
        return STATEMENT_LIST_NODE;
    }

    StatementListNode::StatementListNode() {}

    StatementListNode::StatementListNode(Node *node) {
        this->statements.push_back(node);
    }

    void StatementListNode::push(Node *node) {
        this->statements.push_back(node);
    }


    llvm::Value *StatementListNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "StatementListNode", __FUNCTION__);

        Value *finalValue = nullptr;
        for (auto const &value:this->statements) {
            finalValue = value->codeGen(cxt);
            if (cxt->getCurrentFunction() != nullptr && builder.GetInsertBlock()->getTerminator() != nullptr) {
                return finalValue;
            }
        }

        return finalValue;
    }

}