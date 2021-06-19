//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_INTTYPE_H
#define FLARE_INTTYPE_H

#include "BaseType.h"

namespace flare::types {

    class IntType : public BaseType {

    public:

        Type *getLLVMType(Context *) override;

        Value *createInstance(Context *, LValue) override;

    };

}


#endif //FLARE_INTTYPE_H
