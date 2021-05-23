//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/Context.h>
#include <ast/StatementListNode.h>

void flare::ast::Context::pushFunction(Node *function) {
    functions.push(function);
}

void flare::ast::Context::popFunction() {
    functions.pop();
}

flare::ast::Node *flare::ast::Context::getCurrentFunction() {
    if (this->functions.empty()) {
        return nullptr;
    }
    return functions.top();
}

void flare::ast::Context::pushStatementList(ast::Node *node) {
    this->statementList.push_back(node);
}

void flare::ast::Context::popStatementList() {
    this->statementList.pop_back();
}

flare::ast::Node *flare::ast::Context::getCurrentStatementList() {
    if (this->statementList.empty()) {
        return nullptr;
    }
    return statementList.back();
}