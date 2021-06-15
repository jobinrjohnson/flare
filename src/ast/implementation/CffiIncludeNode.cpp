//
// Created by jobinrjohnson on 15/06/21.
//

#include "ast/CffiIncludeNode.h"

namespace flare::ast {

    llvm::Value *CffiIncludeNode::codeGen(Context *cxt) {
        return nullptr;
    }

    CffiIncludeNode::CffiIncludeNode(std::string name, std::string alias) {
        this->name = name;
        this->alias = alias;
    }
}
