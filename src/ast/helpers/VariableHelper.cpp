//
// Created by jobinrjohnson on 08/05/21.
//

#include "VariableHelper.h"
#include "StatementListNode.h"

namespace ast {
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
                return llvm::Type::getInt64Ty(context);
            case VARTYPE_INT_32:
                return llvm::Type::getInt32Ty(context);
            case VARTYPE_INT_64:
                return llvm::Type::getInt64Ty(context);
            case VARTYPE_FLOAT:
                break;
            case VARTYPE_DOUBLE:
                break;
            case VARTYPE_NUMBER:
                break;
            case OTHER:
                break;
        }
        throw "Type not found";
    }

}