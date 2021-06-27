//
// Created by jobinrjohnson on 12/05/21.
//

#ifndef FLARE_CLASSDECLNODE_H
#define FLARE_CLASSDECLNODE_H

#include "Node.h"
#include "FunctionNode.h"

namespace flare::ast {

    class ClassDeclNode : public Node {

        std::string className;

        std::vector<FunctionNode *> functions;

        std::vector<VarDeclNode *> vars;

        llvm::StructType *LLVMType;

        llvm::PointerType *LLVMPtrType;

        llvm::Function *initFunction;

    public:


        NodeType getNodeType() override;

        explicit ClassDeclNode(const char *name, std::vector<ast::Node *> *nodeList);

        llvm::Value *codeGen(Context *cxt) override;

        llvm::Value *codeGenConstructor(Context *cxt);

        llvm::StructType *getClassLLVMType();

        llvm::PointerType *getClassLLVMPointerType();

        unsigned int getVariableIndex(std::string name);

        llvm::Function *getInitFunction() {
            return this->initFunction;
        }

        std::string getQualifiedClassName();

        friend class ClassObjectType;

    };


}

#endif //FLARE_CLASSDECLNODE_H
