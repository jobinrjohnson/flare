//
// Created by jobinrjohnson on 09/05/21.
//

#ifndef FLARE_ASTCONSTANTS_H
#define FLARE_ASTCONSTANTS_H

#include <string>

namespace flare::ast {

    class Node;

    enum NodeType {
        ASSIGNMENT_NODE,
        EXPR_NODE,
        STATEMENT_NODE,
        LITERAL_NODE,
        STATEMENT_LIST_NODE,
        VAR_DECL_NODE,
        VAR_DEREF_NODE,
        IF_NODE,
        LOG_NODE,
        FUNCTION_NODE,
        VALUE_PLACEHOLDER_NODE,
        LOOP_NODE,
        FUNCTION_CALL_NODE,
        CLASS_DECL_NODE,
        TYPE_CONV_NODE,
        EXCEPTION_HANDLE_NODE,
        EMPTY_NODE
    };

    enum VariableType {
        VARTYPE_BOOLEAN,    // In use
        VARTYPE_INT_32,
        VARTYPE_INT_64,
        VARTYPE_INT,        // In use
        VARTYPE_FLOAT,
        VARTYPE_DOUBLE,     // In use
        VARTYPE_NUMBER,     // In use
        VARTYPE_ARRAY,
        VARTYPE_STRING,     // In Use
        VARTYPE_VOID,       // In use
        OTHER
    };


    enum OperatorType {
        PLUS,
        MINUS,
        MUL,
        DIV,
        SCALAR,
        VAR_DE_REF,
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_EQUAL,
        LESS_THAN_EQUAL,
        EQUALITY,
        NOT_EQUALITY,
        NOT,
        GROUPED,
        UNARY_PLUS,
        UNARY_MINUS,
        MODULO_DIV,
        FUNCTION_CALL,
        LOGICAL_AND,
        LOGICAL_OR,
        ASSIGNMENT
    };

    // Value
    union LValue {
        int iVal;       // integer value
        double dVal;    // double value
        bool bVal;      // boolean value
        char *sVal;     // string value
    };

    typedef struct VarType {
        VariableType type;
        std::string name = "";
    } VarType;


    class Parameter {
    public:
        std::string name;
        VarType *type;

        explicit Parameter(std::string name, VarType *type) {
            this->name = name;
            this->type = type;
        }
    };

}

#endif //FLARE_ASTCONSTANTS_H
