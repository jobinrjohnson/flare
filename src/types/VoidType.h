//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_VOIDTYPE_H
#define FLARE_VOIDTYPE_H

#include "BaseType.h"

namespace flare::types {

    class VoidType : public BaseType {

    public:

        Type *getLLVMType(Context *) override;

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

    };

}

#endif //FLARE_VOIDTYPE_H
