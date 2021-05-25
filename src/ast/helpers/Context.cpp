//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/Context.h>
#include <ast/StatementListNode.h>

namespace flare::ast {

    void Context::pushFunction(Node *function) {
        functions.push(function);
    }

    void Context::popFunction() {
        functions.pop();
    }

    Node *Context::getCurrentFunction() {
        if (this->functions.empty()) {
            return nullptr;
        }
        return functions.top();
    }

    void Context::pushStatementList(ast::Node *node) {
        this->statementList.push_back(node);
    }

    void Context::popStatementList() {
        this->statementList.pop_back();
    }

    Node *Context::getCurrentStatementList() {
        if (this->statementList.empty()) {
            return nullptr;
        }
        return statementList.back();
    }

    llvm::Value *Context::findLocal() {
        return nullptr;
    }

    void Context::pushClassDeclaration(std::string name, Node *classDecl) {
        this->classDeclarations.insert(std::pair<std::string, Node *>(name, classDecl));
    }

    Node *Context::findClassDeclaration(std::string name) {
        auto val = this->classDeclarations.find(name);
        if (val != this->classDeclarations.end()) {
            return val->second;
        }
        return nullptr;
    }

    Node *Context::findVariable(std::string name) {
        VarDeclNode *variable = nullptr;
        std::vector<Node *>::iterator i = this->statementList.end();
        while (i != this->statementList.begin()) {
            --i;
            StatementListNode *node = dynamic_cast<StatementListNode *>(*i);
            variable = node->findLocal(name);
            if (variable != nullptr) {
                return variable;
            }
        }
        return nullptr;
    }
}