//
// Created by jobinrjohnson on 8/3/20.
//

#include <ast/AssignmentNode.h>
#include <ast/helpers/VariableHelper.h>
#include <ast/VarDeclNode.h>

namespace flare::ast {

    AssignmentNode::AssignmentNode(char *name, Node *indexNode, Node *exprNode) {
        this->varName = name;
        this->index = indexNode;
        this->expression = exprNode;
    }

    AssignmentNode::AssignmentNode(char *name, Node *node) {
        this->varName = name;
        this->expression = node;
    }

    llvm::Value *AssignmentNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "AssignmentNode", __FUNCTION__);

        Node *vNode = cxt->findVariable(this->varName);

        if (vNode == nullptr) {
            throw "Invalid variable name";
        }

        auto *variable = dynamic_cast<VarDeclNode *>(vNode);
        Value *value = this->expression->codeGen(cxt->nextLevel());

        if (index != nullptr) {
            auto indexVal = this->index->codeGen(cxt->nextLevel());

            std::vector<llvm::Value *> ind{
                    llvm::ConstantInt::get(context, llvm::APInt(64, 0, false)),
                    indexVal
            };

            auto arrayPtrLoad = builder.CreateGEP(
                    variable->getLLVMVarRef(),
                    ind,
                    "arrayLoad"
            );

            return builder.CreateStore(value, arrayPtrLoad);
        }

        return builder.CreateStore(value, variable->getLLVMVarRef());
    }

    NodeType AssignmentNode::getNodeType() {
        return ASSIGNMENT_NODE;
    }

}