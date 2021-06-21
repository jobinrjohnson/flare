//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/Context.h>
#include <ast/StatementListNode.h>

#include <types/IntType.h>
#include <types/StringType.h>

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

    void Context::addType(llvm::Type *type, Node *node) {
        this->customTypesAvail.insert(std::pair<llvm::Type *, Node *>(type, node));
    }

    Node *Context::getType(llvm::Type *type) {
        auto val = this->customTypesAvail.find(type);
        if (val != this->customTypesAvail.end()) {
            return val->second;
        }
        return nullptr;
    }


    BaseType *Context::findType(std::string name) {
        auto val = this->types.find(name);
        if (val != this->types.end()) {
            return val->second;
        }

        // Register built in types
        BaseType *type = nullptr;
        if (name == "int") {
            type = new IntType();
        } else if (name == "string") {
            type = new StringType();
        }

        if (type != nullptr) {
            this->registerType("int", type);
            return type;
        }
        return nullptr;
    }

    bool Context::registerType(std::string name, BaseType *type) {
        this->types.insert(std::pair<std::string, BaseType *>(name, type));
        return true;
    }


    BaseType *Context::getFlareType(ast::VariableType type) {

        switch (type) {

            case VARTYPE_INT_32:
                break;
            case VARTYPE_INT_64:
            case VARTYPE_INT:
                return this->findType("int");
            case VARTYPE_FLOAT:
                break;
            case VARTYPE_DOUBLE:
                break;
            case VARTYPE_NUMBER:
                break;
            case VARTYPE_BOOLEAN:
                break;
            case VARTYPE_ARRAY:
                break;
            case VARTYPE_STRING:
                return this->findType("string");
            case VARTYPE_VOID:
                break;
            case VARTYPE_OBJECT:
                break;
            case OTHER:
                break;
        }

        throw "this wont work";
    }

    BaseType *Context::getFlareType(VarType type) {
        return this->getFlareType(type.type);
    }


}