//
// Created by jobinrjohnson on 05/05/21.
//

#ifndef FLARE_FUNCTIONNODE_H
#define FLARE_FUNCTIONNODE_H


#include "Node.h"
#include "StatementListNode.h"
#include "constants/AstConstants.h"

namespace ast {

    class FunctionNode : public Node {

    protected:
        // Name of the function
        std::string name;

        // List of parameters
        std::vector<ast::Parameter *> *parameterList;

        // Function body
        StatementListNode *statementListNode;

        // The class node only if the function belongs to a class
        Node *classNode = nullptr;

        // If the node has multiple exits
        bool hasMultipleExits = false;

        // Return returnType of the function
        VarType *returnType = nullptr;

        void prepareBlocks();

    public:

        BasicBlock *entryBlock;
        BasicBlock *exitBlock;
        Function *function;
        AllocaInst *retValue;

        NodeType getNodeType() override;

        explicit FunctionNode(const char *name, StatementListNode *statements, VarType *type);

        explicit FunctionNode(const char *name, StatementListNode *statements, VarType *type,
                              std::vector<ast::Parameter *> *parameterList);

        llvm::FunctionType *codeGenSignature(Context *cxt);

        llvm::Value *codeGen(Context *cxt) override;

        void setHasMultipleExits();

        // Returns the function return type
        inline VarType *getReturnType() {
            if (this->returnType == nullptr) {
                throw "Return type of the function is not defined";
            }
            return this->returnType;
        }

        // Sets the function return type
        inline void setReturnType(VarType *type) {
            this->returnType = type;
        }

        // Sets the class for the function. if it is a part of a class
        inline void setClass(Node *classNodePointer) {
            this->classNode = classNodePointer;
        }

        // Return if the function is a class function or not
        inline bool isClassFunction() {
            return this->classNode != nullptr;
        }

        ~FunctionNode() {
            free(this->statementListNode);
            free(this->classNode);
            for (auto ele : *(this->parameterList)) {
                free(ele);
            }
            free(this->parameterList);
        }

    };
}


#endif //FLARE_FUNCTIONNODE_H
