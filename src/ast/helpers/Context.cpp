//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/helpers/Context.h>
#include <ast/StatementListNode.h>

#include <types/IntType.h>
#include <types/StringType.h>

#include <iostream>
#include <types/BoolType.h>
#include <types/DoubleType.h>
#include <types/VoidType.h>
#include <types/ClassObjectType.h>

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

    VarDeclNode *Context::findVariable(std::string name) {
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
        return nullptr;
    }

    bool Context::registerType(std::string name, BaseType *type) {

        std::cout << "<<" << name << std::endl;
        if (this->findType(name) != nullptr) {
            throw "already in";
        }

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
            case VARTYPE_NUMBER:
                return this->findType("double");
            case VARTYPE_BOOLEAN:
                return this->findType("boolean");
            case VARTYPE_ARRAY:
                break;
            case VARTYPE_STRING:
                return this->findType("string");
            case VARTYPE_VOID:
                std::cout << type << std::endl;
                break;
            case OTHER:
                break;
        }

        throw "this wont work";
    }

    BaseType *Context::getFlareType(VarType type) {

        if (type.type == VariableType::OTHER) {
            return this->findType(type.name);
        }

        return this->getFlareType(type.type);
    }

    BaseType *Context::getFlareType(Value *value) {
        for (auto const &x : this->types) {
            Type *valType = value->getType();

            AllocaInst *inst;
            if ((inst = static_cast<AllocaInst *>(value))) {
                valType = inst->getAllocatedType();
            }

            std::cout << ">>" << x.first << " ->" << valType << std::endl;
            if (x.second->getLLVMType(this) == valType) {
                return x.second;
            }

            if (x.second->getLLVMType(this) == valType) {
                return x.second;
            }
        }
        throw "Type not found";
    }

    void Context::initTypes() {
        this->registerType("int", new IntType());
        this->registerType("string", new StringType());
        this->registerType("boolean", new BoolType());
        this->registerType("double", new DoubleType());
        this->registerType("void", new VoidType());
    }


}