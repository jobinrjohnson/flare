//
// Created by jobinrjohnson on 05/05/21.
//

#include "Context.h"

void ast::Context::pushFunction(FunctionNode *function) {
    functions.push(function);
}

void ast::Context::popFunction() {
    functions.pop();
}

ast::FunctionNode *ast::Context::getCurrentFunction() {
    if (this->functions.empty()) {
        return nullptr;
    }
    return functions.top();
}
