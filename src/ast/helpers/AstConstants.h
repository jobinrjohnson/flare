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

    typedef struct {
        VariableType type;
        std::string name; // Valid only if type is other
    } VarType;

}

#endif //FLARE_ASTCONSTANTS_H
