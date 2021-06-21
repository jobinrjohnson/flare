//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_BOOLTYPE_H
#define FLARE_BOOLTYPE_H


#include "BaseType.h"

namespace flare::types {

    class BoolType : public BaseType {

    public:

        Type *getLLVMType(Context *) override;

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

    };

}


#endif //FLARE_BOOLTYPE_H
