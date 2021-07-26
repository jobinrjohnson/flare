//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/StatementListNode.h>

namespace flare::ast {

    llvm::Type *getLLVMType(ast::VariableType type, llvm::LLVMContext &context) {
        switch (type) {
            case VARTYPE_INT:
            case VARTYPE_INT_64:
                return llvm::Type::getInt64Ty(context);
            case VARTYPE_INT_32:
                return llvm::Type::getInt32Ty(context);
            case VARTYPE_FLOAT:
                return llvm::Type::getFloatTy(context);
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return llvm::Type::getDoubleTy(context);
            case VARTYPE_BOOLEAN:
                return llvm::Type::getInt1Ty(context);
            case VARTYPE_VOID:
                return llvm::Type::getVoidTy(context);
            case OTHER:
            case VARTYPE_STRING:
                return llvm::Type::getInt8PtrTy(context);
            case VARTYPE_ARRAY:
                throw "LLVM Type not defined.";
                break;
        }
        throw "Type not found";
    }

}