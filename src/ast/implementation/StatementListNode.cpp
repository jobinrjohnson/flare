//
// Created by jobinrjohnson on 7/23/20.
//

#include <ast/StatementListNode.h>

namespace flare::ast {

    extern Context *globalContext;
    extern std::vector<Node *> lopStatementLists;


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

        if (globalContext != nullptr) {
            this->locals.clear();
        }

        this->printCallStack(cxt, "StatementListNode", __FUNCTION__);

        cxt->pushStatementList(this);

        Value *finalValue = nullptr;
        for (auto const &value: this->statements) {
            finalValue = value->codeGen(cxt);
            if (cxt->getCurrentFunction() != nullptr && builder.GetInsertBlock()->getTerminator() != nullptr) {
                goto end;
            }
        }
        end:
        cxt->popStatementList();
        if (globalContext != nullptr) {
            lopStatementLists.push_back(this);
        }
        return finalValue;
    }


    void ast::StatementListNode::createLocal(const std::string &varName, VarDeclNode *value) {
        this->locals.insert(std::pair<std::string, VarDeclNode *>(varName, value));
    }

    VarDeclNode *ast::StatementListNode::findLocal(const std::string &varName) {
        auto val = this->locals.find(varName);
        if (val != this->locals.end()) {
            return val->second;
        }
        return nullptr;
    }

    void StatementListNode::pushFirst(Node *node) {
        this->statements.insert(this->statements.begin(), node);
    }


}