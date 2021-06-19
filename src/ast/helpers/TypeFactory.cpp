//
// Created by jobinrjohnson on 19/06/21.
//

#include <types/IntType.h>
#include <types/StringType.h>
#include "TypeFactory.h"

namespace flare::ast::helpers {

    BaseType *TypeFactory::getFlareType(ast::VariableType type) {

        switch (type) {

            case VARTYPE_INT_32:
                break;
            case VARTYPE_INT_64:
            case VARTYPE_INT:
                return new IntType();
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
                return new StringType();
            case VARTYPE_VOID:
                break;
            case VARTYPE_OBJECT:
                break;
            case OTHER:
                break;
        }

        throw "this wont work";

        return nullptr;
    }

    BaseType *TypeFactory::getFlareType(VarType type) {
        return this->getFlareType(type.type);
    }

}
