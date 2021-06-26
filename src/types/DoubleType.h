//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_DOUBLETYPE_H
#define FLARE_DOUBLETYPE_H

#include "BaseType.h"

namespace flare::types {

    class DoubleType : public BaseType {

    protected:
        Type *probeLLVMType(Context *) override;

    public:

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

        Type *getLLVMPtrType(Context *) override;

    };

}


#endif //FLARE_DOUBLETYPE_H
