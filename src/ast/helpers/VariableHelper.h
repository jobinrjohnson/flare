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

    void typePromote(std::vector<llvm::Value *> *ops, llvm::LLVMContext &context, llvm::IRBuilder<> &builder);

    llvm::Value *castTo(llvm::Value *value, CastTo to);

    llvm::Value *castTo(llvm::Value *value, VarType *to);
}


#endif //FLARE_VARIABLEHELPER_H
