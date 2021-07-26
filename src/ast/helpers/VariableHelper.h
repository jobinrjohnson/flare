//
// Created by jobinrjohnson on 08/05/21.
//

#ifndef FLARE_VARIABLEHELPER_H
#define FLARE_VARIABLEHELPER_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <ast/helpers/Context.h>
#include <ast/constants/AstConstants.h>

namespace flare::ast {

    llvm::Type *getLLVMType(ast::VariableType type, llvm::LLVMContext &context);
}


#endif //FLARE_VARIABLEHELPER_H
