//
// Created by jobinrjohnson on 08/05/21.
//

#ifndef FLARE_FUNCTIONCALLNODE_H
#define FLARE_FUNCTIONCALLNODE_H

#include "Node.h"
#include "ExprNode.h"

namespace flare::ast {
    class FunctionCallNode : public Node {

    protected:

        std::string functionName;

        std::vector<ExprNode *> *argumentList;

        std::string className;

        std::string objectName;

        llvm::Value *performCall(Function * calleeFunction, ArrayRef<Value *> Args = None);

    public:

        FunctionCallNode();

        explicit FunctionCallNode(std::string functionName);

        explicit FunctionCallNode(std::string functionName, std::vector<ExprNode *> *argumentList);

        NodeType getNodeType() override {
            return NodeType::FUNCTION_CALL_NODE;
        }

        llvm::Value *codeGen(Context *cxt) override;

        llvm::Value *codeGenObjectCreate(Context *cxt);

        llvm::Value *codeGenObjectFunction(Context *cxt);

        inline void setArgumentList(std::vector<ExprNode *> *args) {
            this->argumentList = args;
        }

        inline void setClassName(std::string cName) {
            this->className = cName;
        }

        inline void setObjectName(std::string oName) {
            this->objectName = oName;
        }

        inline bool isObjectCreation() {
            return this->className.length() != 0;
        }

        inline bool isClassFunction() {
            return this->objectName.length() != 0;
        }

    };

}

#endif //FLARE_FUNCTIONCALLNODE_H
