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
}