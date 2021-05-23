//
// Created by jobinrjohnson on 09/05/21.
//

#ifndef FLARE_ASTCONSTANTS_H
#define FLARE_ASTCONSTANTS_H

namespace flare::ast {

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
        CLASS_DECL_NODE
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
        OTHER
    };

    enum CastTo {
        PR_TY_INT_32, PR_TY_INT_64, PR_TY_FLOAT, PR_TY_DOUBLE, PR_TY_BOOLEAN
    };

    typedef struct {
        VariableType type;
        VariableType subType;
        std::string name; // Valid only if returnType is other
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
