//
// Created by jobinrjohnson on 8/3/20.
//

#include "AssignmentNode.h"

namespace ast {

    AssignmentNode::AssignmentNode(char *name, Node *indexNode, Node *exprNode) {
        this->varName = name;
        this->index = indexNode;
        this->expression = exprNode;
    }

    AssignmentNode::AssignmentNode(char *name, Node *node) {
        this->varName = name;
        this->expression = node;
    }

    llvm::Value *AssignmentNode::codeGen(int depth) {
        this->printCallStack(depth, "AssignmentNode", __FUNCTION__);

        auto variable = module->getGlobalVariable(this->varName);
        Value *value = this->expression->codeGen(depth + 1);

        if (index != nullptr) {
            auto indexVal = this->index->codeGen(depth + 1);

            std::vector<llvm::Value *> ind{
                    llvm::ConstantInt::get(context, llvm::APInt(64, 0, false)),
                    indexVal
            };

            auto arrayPtrLoad = builder.CreateGEP(
                    variable,
                    ind,
                    "arrayLoad"
            );

            return builder.CreateStore(value, arrayPtrLoad);
        }

        return builder.CreateStore(value, variable);
    }

    NodeType AssignmentNode::getNodeType() {
        return ASSIGNMENT_NODE;
    }

}