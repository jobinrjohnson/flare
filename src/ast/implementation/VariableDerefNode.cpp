//
// Created by jobinrjohnson on 8/3/20.
//

#include <ast/VariableDerefNode.h>
#include <ast/VarDeclNode.h>
#include <exceptions/SemanticException.h>
#include <types/ClassObjectType.h>

namespace flare::ast {


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

        if (!this->base.empty()) {

            VarDeclNode *vNode = cxt->findVariable(this->base);
            if (vNode == nullptr) {
                throw new exceptions::SemanticException("Variable '"
                                                        + this->base
                                                        + "' is not defined in this scope",
                                                        this->lineNumber
                );
            }

            BaseType *fType = vNode->getFlareType();

            if (auto classType = dynamic_cast<ClassObjectType *>(fType)) {
                auto *load = builder.CreateLoad(vNode->getLLVMVarRef());
                unsigned int index = classType->getVariableIndex(this->variableName);
                auto *itemPointer = builder.CreateStructGEP(load, index);
                return builder.CreateLoad(itemPointer);
            }
            // TODO handle more types

            throw "VariableDerefNode: type not handled";

        }


        Node *vNode = cxt->findVariable(this->variableName);
        if (vNode == nullptr) {
            throw new exceptions::SemanticException("Variable '"
                                                    + this->variableName
                                                    + "' is not defined in this scope",
                                                    this->lineNumber
            );
        }

        auto *variable = dynamic_cast<VarDeclNode *>(vNode);

        if (this->isArrayDeReference) {

            auto index = this->arrayIndex->codeGen(cxt);
            return variable->getFlareType()->apply(OperatorType::VAR_DE_REF, {variable->getLLVMVarRef(), index});

//            std::vector<llvm::Value *> ind{
//                    llvm::ConstantInt::get(context, llvm::APInt(64, 0, false)),
//                    index
//            };
//            auto arrayPtrLoad = builder.CreateGEP(
//                    variable->getLLVMVarRef(),
//                    ind,
//                    "arrayLoad"
//            );
//
//            return builder.CreateLoad(arrayPtrLoad);

        }
        return builder.CreateLoad(variable->getLLVMVarRef());

    }

    VariableDerefNode::VariableDerefNode(const char *mLiteralValue, const char *base) {
        this->base = base;
        this->variableName = mLiteralValue;
    }

}
