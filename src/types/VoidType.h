//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_VOIDTYPE_H
#define FLARE_VOIDTYPE_H

#include "BaseType.h"

namespace flare::types {

    class VoidType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

        Value *getDefaultValue(Context *) override;

    };

}

#endif //FLARE_VOIDTYPE_H
