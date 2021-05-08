//
// Created by jobinrjohnson on 08/05/21.
//

#ifndef FLARE_VARIABLEHELPER_H
#define FLARE_VARIABLEHELPER_H

#include <llvm/IR/Value.h>
#include "Context.h"

namespace ast {
    llvm::Value *findVariable(Context *cxt, std::string name);
}


#endif //FLARE_VARIABLEHELPER_H
