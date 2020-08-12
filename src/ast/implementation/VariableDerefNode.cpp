//
// Created by jobinrjohnson on 8/3/20.
//

#include "VariableDerefNode.h"

namespace ast {


    NodeType VariableDerefNode::getNodeType() {
        return VAR_DEREF_NODE;
    }

    VariableDerefNode::VariableDerefNode(char *mLiteralValue) {
        this->variableName = mLiteralValue;
    }

    VariableDerefNode::VariableDerefNode(char *mLiteralValue, Node *index) {
        this->variableName = mLiteralValue;
        this->arrayIndex = index;
        this->isArrayDeReference = true;
    }

    llvm::Value *VariableDerefNode::codeGen(int depth) {
        this->printCallStack(depth, "VariableDerefNode", __FUNCTION__);

        auto gVar = module->getNamedGlobal(this->variableName);
        if (!gVar) {
            throw "no global variable declared with the name"; // TODO throw proper error
        }

        if (this->isArrayDeReference) {

            auto index = this->arrayIndex->codeGen(depth + 1);

            std::vector<llvm::Value *> ind{
                    llvm::ConstantInt::get(context, llvm::APInt(64, 0, false)),
                    index
            };

            auto arrayPtrLoad = builder.CreateGEP(
                    gVar,
                    ind,
                    "arrayLoad"
            );

            return builder.CreateLoad(arrayPtrLoad);

        }

        return builder.CreateLoad(gVar, this->variableName);

    }

}
