//
// Created by jobinrjohnson on 09/05/21.
//

#ifndef FLARE_ASTCONSTANTS_H
#define FLARE_ASTCONSTANTS_H

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
        EMPTY_NODE
    };

    enum VariableType {
        VARTYPE_INT_32,
        VARTYPE_INT_64,
        VARTYPE_INT,
        VARTYPE_FLOAT,
        VARTYPE_DOUBLE,
        VARTYPE_NUMBER,
        VARTYPE_BOOLEAN,
        VARTYPE_ARRAY,
        VARTYPE_STRING,
        VARTYPE_VOID,
        VARTYPE_OBJECT,
        OTHER
    };

    // Value
    union LValue {
        int iVal;       // integer value
        double dVal;    // double value
        bool bVal;      // boolean value
        char *sVal;     // string value
    };

    enum CastTo {
        PR_TY_INT_32, PR_TY_INT_64, PR_TY_FLOAT, PR_TY_DOUBLE, PR_TY_BOOLEAN
    };

    union TypeReference {
        std::string name; // Valid only if returnType is other
        Node *node;
    };

    typedef struct VarType {
        VariableType type;
        VariableType subType = OTHER;
        TypeReference *typeRef;
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
