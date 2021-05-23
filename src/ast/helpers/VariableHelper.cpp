//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/StatementListNode.h>

namespace flare::ast {
    llvm::Value *findVariable(Context *cxt, std::string name) {
        llvm::Value *variable = nullptr;
        std::vector<Node *>::iterator i = cxt->statementList.end();
        while (i != cxt->statementList.begin()) {
            --i;
            StatementListNode *node = dynamic_cast<StatementListNode *>(*i);
            variable = node->findLocal(name);
            if (variable != nullptr) {
                return variable;
            }
        }
        return nullptr;
    }

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
            case OTHER:
            case VARTYPE_ARRAY:
                throw "Conversion not defined.";
                break;
        }
        throw "Type not found";
    }

    llvm::Value *castTo(llvm::Value *value, CastTo to) {

        llvm::Value *returnVal = value;
        Type *varType = value->getType();
        switch (to) {
            case PR_TY_INT_32: {
                if (varType->isIntegerTy(64)) {
                    returnVal = builder.CreateIntCast(value, getLLVMType(VARTYPE_INT_32, context), true);
                } else if (varType->isFloatTy() || varType->isDoubleTy()) {
                    returnVal = builder.CreateFPToSI(value, getLLVMType(VARTYPE_INT_32, context));
                }
                break;
            }
            case PR_TY_INT_64: {
                if (varType->isIntegerTy(32)) {
                    returnVal = builder.CreateIntCast(value, getLLVMType(VARTYPE_INT_64, context), true);
                } else if (varType->isFloatTy() || varType->isDoubleTy()) {
                    returnVal = builder.CreateFPToSI(value, getLLVMType(VARTYPE_INT_64, context));
                }
                break;
            }
            case PR_TY_FLOAT: {
                if (varType->isIntegerTy()) {
                    returnVal = builder.CreateSIToFP(value, getLLVMType(VARTYPE_FLOAT, context));
                } else if (varType->isDoubleTy()) {
                    returnVal = builder.CreateFPCast(value, getLLVMType(VARTYPE_FLOAT, context));
                }
                break;
            }
            case PR_TY_DOUBLE: {
                if (varType->isIntegerTy()) {
                    returnVal = builder.CreateSIToFP(value, getLLVMType(VARTYPE_DOUBLE, context));
                } else if (varType->isFloatTy()) {
                    returnVal = builder.CreateFPCast(value, getLLVMType(VARTYPE_DOUBLE, context));
                }
                break;
            }
            case PR_TY_BOOLEAN:
                throw "Other types cannot be converted to boolean";
        }

        return returnVal;

    }

    llvm::Value *castTo(llvm::Value *value, VarType *to) {

        switch (to->type) {

            case VARTYPE_INT_32:
                return castTo(value, PR_TY_INT_32);
            case VARTYPE_INT_64:
            case VARTYPE_INT:
                return castTo(value, PR_TY_INT_64);
            case VARTYPE_FLOAT:
                return castTo(value, PR_TY_FLOAT);
            case VARTYPE_DOUBLE:
            case VARTYPE_NUMBER:
                return castTo(value, PR_TY_DOUBLE);
            case VARTYPE_BOOLEAN:
                return castTo(value, PR_TY_BOOLEAN);
                break;
            case VARTYPE_ARRAY:
            case OTHER:
                break;
        }

        throw "Unable to cast to specified returnType;";

    }

    void typePromote(std::vector<llvm::Value *> *ops, llvm::LLVMContext &context, llvm::IRBuilder<> &builder) {

        CastTo to = PR_TY_INT_32;

        // Find the correct cast to
        auto i = ops->begin();
        while (i < ops->end()) {
            llvm::Value *value = (*i);
            Type *varType = value->getType();
            if (varType->isIntegerTy(32) && to < PR_TY_INT_32) {
                to = PR_TY_INT_32;
            } else if (varType->isIntegerTy(64) && to < PR_TY_INT_64) {
                to = PR_TY_INT_64;
            } else if (varType->isFloatTy() && to < PR_TY_FLOAT) {
                to = PR_TY_FLOAT;
            } else if (varType->isDoubleTy() && to < PR_TY_DOUBLE) {
                to = PR_TY_DOUBLE;
            }
            i++;
        }
        i = ops->begin();
        // TODO sign
        while (i < ops->end()) {
            *i = castTo(*i, to);
            i++;
        }

    }

}