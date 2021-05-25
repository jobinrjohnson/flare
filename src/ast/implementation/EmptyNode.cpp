//
// Created by jobinrjohnson on 25/05/21.
//

#include <ast/EmptyNode.h>

namespace flare::ast {
    EmptyNode::EmptyNode(Value *value) {
        this->llvmValue = value;
    }

    llvm::Value *EmptyNode::codeGen(Context *cxt) {
        return this->llvmValue;
    }
}
