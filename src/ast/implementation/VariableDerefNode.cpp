//
// Created by jobinrjohnson on 8/3/20.
//

#include "VariableDerefNode.h"
#include "FunctionNode.h"
#include "helpers/VariableHelper.h"

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

    llvm::Value *VariableDerefNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "VariableDerefNode", __FUNCTION__);


        Value *variable = findVariable(cxt, this->variableName);
        if (variable == nullptr) {
            throw "no global variable declared in the scope";
        }

        if (this->isArrayDeReference) {

            auto index = this->arrayIndex->codeGen(cxt);

            std::vector<llvm::Value *> ind{
                    llvm::ConstantInt::get(context, llvm::APInt(64, 0, false)),
                    index
            };

            auto arrayPtrLoad = builder.CreateGEP(
                    variable,
                    ind,
                    "arrayLoad"
            );

            return builder.CreateLoad(arrayPtrLoad);

        }
        return builder.CreateLoad(variable);

    }

}
