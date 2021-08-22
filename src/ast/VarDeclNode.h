//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_VARDECLNODE_H
#define FLARE_VARDECLNODE_H


#include <types/BaseType.h>
#include "Node.h"
#include "LiteralNode.h"
#include "constants/AstConstants.h"

namespace flare::ast {

    class VarDeclNode : public Node {

    protected:

        // Name of the variable
        std::string variableName;

        // Initial value AST node
        Node *initialValue = nullptr;

        // The class node if it is a class member
        Node *classNode = nullptr;

        // The function node if it is a function
        Node *functionNode = nullptr;

        // Tpe of the variable
        VarType *type = nullptr;

        // LLVM Variable reference
        Value *llvmVarRef;

        types::BaseType *flareType;

        // Functions

        // Code generation for built in types
        Value *codeGenBuiltInTy(Context *);

        // Code generation for array types
        Value *codeGenArray(Context *cxt);

    public:

        // Sets the variable initial value
        inline void setInitialValue(Node *variableInitialValue) {
            this->initialValue = variableInitialValue;
        }

        // Sets the variable type
        inline void setVarType(VarType *variableType) {
            this->type = variableType;
        }

        // Sets the class node
        inline void setClass(Node *variableClassNode) {
            this->classNode = variableClassNode;
        }

        inline bool isClassVariable() {
            return this->classNode != nullptr;
        }

        // Returns the LLVM variable reference
        inline Value *getLLVMVarRef() {
            return this->llvmVarRef;
        }

        // Returns the internal type
        inline BaseType *getFlareType() {
            return this->flareType;
        }

        // Returns the variable name
        inline std::string getVariableName() {
            return this->variableName;
        }

        inline VarType *getVariableType() {
            return this->type;
        }

        llvm::Type *getVariableLLVMType(Context *cxt);

        // Returns the node types (for debugging)
        NodeType getNodeType() override;

        // Constructor only name
        VarDeclNode(char *name);

        // Constructor name and variable type.
        VarDeclNode(const char *name, VarType *type);

        // Constructor name and variable type.
        VarDeclNode(const char *name, BaseType *type);

        // Generate code for the node (Post AST function)
        llvm::Value *codeGen(Context *cxt) override;

        // Generate code if the node corresponds to a global variable
        llvm::Value *codeGenGlobalVariable(Context *cxt);

        // Generate code if the node corresponds to a local variable
        llvm::Value *codeGenLocalVariable(Context *cxt);

        inline bool hasInitializer() {
            return this->initialValue != nullptr;
        }

        inline Node *getInitializer() {
            return this->initialValue;
        }


        ~VarDeclNode() {

            delete (initialValue);
            delete (classNode);
            delete (functionNode);
            delete (type);
//            delete (flareType);

        }

    };

}

#endif //FLARE_VARDECLNODE_H
