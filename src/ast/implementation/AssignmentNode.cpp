//
// Created by jobinrjohnson on 8/3/20.
//

#include <ast/AssignmentNode.h>
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

        if (index != nullptr) {
            return this->codeGenArrayAssign(cxt);
        }

        Node *vNode = cxt->findVariable(this->varName);
        if (vNode == nullptr) {
            throw "Invalid variable name";
        }


        auto *variable = dynamic_cast<VarDeclNode *>(vNode);
        Value *value = this->expression->codeGen(cxt->nextLevel());


        if (!cxt->getFlareType(value)->isInbuiltTy()) {

            auto bCst1 = builder.CreateBitCast(value, Type::getInt8PtrTy(*cxt->getLLVMContext()));
            auto bCst2 = builder.CreateBitCast(variable->getLLVMVarRef(), Type::getInt8PtrTy(*cxt->getLLVMContext()));

            builder.CreateMemCpy(bCst2, MaybeAlign(8), bCst1, MaybeAlign(8), 8);

        } else {
            builder.CreateStore(value, variable->getLLVMVarRef());
        }

        return value;
    }

    NodeType AssignmentNode::getNodeType() {
        return ASSIGNMENT_NODE;
    }

    // TODO refactor later
    llvm::Value *AssignmentNode::codeGenArrayAssign(Context *cxt) {
        Node *vNode = cxt->findVariable(this->varName);

        if (vNode == nullptr) {
            throw "Invalid variable name";
        }

        auto *variable = dynamic_cast<VarDeclNode *>(vNode);
        Value *value = this->expression->codeGen(cxt->nextLevel());
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

        builder.CreateStore(value, arrayPtrLoad);
        return value;
    }

    llvm::Value *AssignmentNode::codeGenObjectAssign(Context *cxt) {
        return nullptr;
    }

}