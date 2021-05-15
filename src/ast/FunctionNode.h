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
        std::vector<Parameter *> *parameterList;

        // Function body
        StatementListNode *statementListNode;

        // The class node only if the function belongs to a class
        Node *classNode = nullptr;

        // LLVM function reference
        Function *function;

        // If the node has multiple exits
        bool hasMultipleExits = false;

        // Return returnType of the function
        VarType *returnType = nullptr;

        // Function entry block
        BasicBlock *entryBlock;

        // Function exit block. Only defined in the case of functions with multiple branches.
        BasicBlock *exitBlock;

        // Function return value stack variable. Only defined in the
        // case of functions with multiple branches.
        AllocaInst *retValue;


        // Codegen for function signature
        FunctionType *codeGenSignature(Context *cxt);

        // Codegen for the exit block
        Value *codeGenExit(Context *cxt);

    public:


        inline NodeType getNodeType() override {
            return FUNCTION_NODE;
        }

        // function without parameter
        explicit FunctionNode(
                const char *name,
                StatementListNode *statements,
                VarType *type
        );

        // function with parameter list
        explicit FunctionNode(
                const char *name,
                StatementListNode *statements,
                VarType *type,
                std::vector<Parameter *> *parameterList
        );

        // Node:codegen override
        Value *codeGen(Context *cxt) override;

        // Generates code for the return value.
        Value *setFunctionReturn(Value *returnValue);

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

        // Destructor
        ~FunctionNode();

    };
}


#endif //FLARE_FUNCTIONNODE_H
