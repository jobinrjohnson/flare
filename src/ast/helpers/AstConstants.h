//
// Created by jobinrjohnson on 09/05/21.
//

#ifndef FLARE_ASTCONSTANTS_H
#define FLARE_ASTCONSTANTS_H

namespace ast {

    enum VariableType {
        VARTYPE_INT_32,
        VARTYPE_INT_64,
        VARTYPE_INT,
        VARTYPE_FLOAT,
        VARTYPE_DOUBLE,
        VARTYPE_NUMBER,
        OTHER
    };

    enum CastTo {
        PR_TY_INT_32, PR_TY_INT_64, PR_TY_FLOAT, PR_TY_DOUBLE
    };

    typedef struct {
        VariableType type;
        std::string name; // Valid only if type is other
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
