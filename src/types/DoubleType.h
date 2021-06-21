//
// Created by jobinrjohnson on 21/06/21.
//

#ifndef FLARE_DOUBLETYPE_H
#define FLARE_DOUBLETYPE_H

#include "BaseType.h"

namespace flare::types {

    class DoubleType : public BaseType {

    public:

        Type *getLLVMType(Context *) override;

        inline bool isInbuiltTy() override {
            return true;
        }

        Value *createInstance(Context *, LValue) override;

    };

}


#endif //FLARE_DOUBLETYPE_H
