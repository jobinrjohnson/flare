//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_TYPEFACTORY_H
#define FLARE_TYPEFACTORY_H

#include <types/BaseType.h>
#include <ast/constants/AstConstants.h>

using namespace flare::types;

namespace flare::ast::helpers {
    class TypeFactory {

    public:
        BaseType *getFlareType(VariableType type);

        BaseType *getFlareType(VarType type);

    };
}


#endif //FLARE_TYPEFACTORY_H
