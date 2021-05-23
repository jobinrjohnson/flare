//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/Context.h>
#include <ast/StatementListNode.h>

void ast::Context::pushFunction(Node *function) {
    functions.push(function);
}

void ast::Context::popFunction() {
    functions.pop();
}

ast::Node *ast::Context::getCurrentFunction() {
    if (this->functions.empty()) {
        return nullptr;
    }
    return functions.top();
}

void ast::Context::pushStatementList(ast::Node *node) {
    this->statementList.push_back(node);
}

void ast::Context::popStatementList() {
    this->statementList.pop_back();
}

ast::Node *ast::Context::getCurrentStatementList() {
    if (this->statementList.empty()) {
        return nullptr;
    }
    return statementList.back();
}