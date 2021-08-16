//
// Created by jobinrjohnson on 17/06/21.
//

#ifndef FLARE_TYPECONVNODE_H
#define FLARE_TYPECONVNODE_H


#include "Node.h"

namespace flare::ast {
    class TypeConvNode : public Node {

    protected:
        std::vector<Value *> operands;

        Type *targetType;

    public:

        NodeType getNodeType() override;

        TypeConvNode(Value *operand);

        inline void addOperand(Value *operand) {
            this->operands.push_back(operand);
        }

        inline bool isExplicitTypeCast() {
            return targetType != nullptr;
        }

        Type *getTargetType();

        llvm::Value *codeGen(Context *cxt) override;

        ~TypeConvNode() override {

        }

    };
}


#endif //FLARE_TYPECONVNODE_H
