//
// Created by jobinrjohnson on 19/06/21.
//

#ifndef FLARE_STRINGTYPE_H
#define FLARE_STRINGTYPE_H

#include "BaseType.h"

namespace flare::types {


    class StringType : public BaseType {

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


#endif //FLARE_STRINGTYPE_H
