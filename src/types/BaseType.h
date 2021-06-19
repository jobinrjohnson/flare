//
// Created by jobinrjohnson on 18/06/21.
//

#ifndef FLARE_BASETYPE_H
#define FLARE_BASETYPE_H

#include <llvm/IR/IRBuilder.h>
#include <ast/constants/AstConstants.h>
#include <ast/helpers/Context.h>

using namespace llvm;
using namespace flare::ast;

namespace flare::types {

    class BaseType {

    public:

        virtual Type *getLLVMType(Context *) = 0;

        virtual Value *createInstance(Context *, LValue) = 0;

    };

}

#endif //FLARE_BASETYPE_H
