//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_INTTYPE_H
#define FLARE_INTTYPE_H

#include "BaseType.h"

namespace flare::types {

    class IntType : public BaseType {

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


#endif //FLARE_INTTYPE_H
