//
// Created by jobinrjohnson on 12/05/21.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/ClassDeclNode.h>
#include <exceptions/SemanticException.h>
#include <types/ClassObjectType.h>

namespace flare::ast {

    NodeType ClassDeclNode::getNodeType() {
        return CLASS_DECL_NODE;
    }

    llvm::Value *ClassDeclNode::codeGen(Context *cxt) {

        // Codegen for class variables
        std::vector<llvm::Type *> items;
        for (VarDeclNode *ele:this->vars) {
            items.push_back(ele->getVariableLLVMType(cxt));
        }

        // Create LLVM type
        this->LLVMType = StructType::create(context, items, this->getQualifiedClassName());

        cxt->addType(this->LLVMType, this);

        cxt->pushClassDeclaration(this->getQualifiedClassName(), this);

        cxt->registerType(
                this->className,
                new ClassObjectType(this)
        );


        this->codeGenConstructor(cxt);

        // Codegen for class functions
        for (FunctionNode *ele:this->functions) {
            ele->codeGen(cxt);
        }

        return nullptr;
    }

    ClassDeclNode::ClassDeclNode(const char *name, std::vector<Node *> *nodeList) {

        this->className = name;

        for (Node *ele:(*nodeList)) {
            FunctionNode *functionNode = nullptr;
            if ((functionNode = dynamic_cast<FunctionNode *>(ele)) != nullptr) {
                functionNode->setClass(this);
                this->functions.push_back(functionNode);
                continue;
            }

            VarDeclNode *varDeclNode = nullptr;
            if ((varDeclNode = dynamic_cast<VarDeclNode *>(ele)) != nullptr) {
                varDeclNode->setClass(this);
                this->vars.push_back(varDeclNode);
                continue;
            }
        }

    }

    llvm::StructType *ClassDeclNode::getClassLLVMType() {
        if (this->LLVMType == nullptr) {
            throw "LLVM type not defined in the class. Please call codegen";
        }
        return this->LLVMType;
    }

    llvm::Value *ClassDeclNode::codeGenConstructor(Context *cxt) {

        std::vector<Type *> argVector;
        argVector.push_back(this->getClassLLVMPointerType());

        auto *funcType = FunctionType::get(
                Type::getVoidTy(*cxt->getLLVMContext()),
                argVector,
                false
        );

        this->initFunction = Function::Create(
                funcType,
                GlobalValue::ExternalLinkage,
                this->getQualifiedClassName() + "::.init", module.get()
        );


        Function::arg_iterator actualArgs = this->initFunction->arg_begin();

        builder.SetInsertPoint(BasicBlock::Create(context, "entry", this->initFunction));
        // prepare vars
        auto inst = builder.CreateAlloca(this->getClassLLVMPointerType(), 0, "this");
        builder.CreateStore(actualArgs, inst);

        auto load = builder.CreateLoad(inst, "var");

        // store some val on struct
        auto ptrLoad =
                builder.CreateStructGEP(
                        load,
                        0,
                        "member"
                );

        auto val = llvm::ConstantInt::get(*cxt->getLLVMContext(), APInt(64, 100));

        builder.CreateStore(val, ptrLoad);

        builder.CreateRet(nullptr);

        return nullptr;
    }

    llvm::PointerType *ClassDeclNode::getClassLLVMPointerType() {
        if (this->LLVMPtrType == nullptr) {
            this->LLVMPtrType = PointerType::get(this->getClassLLVMType(), 0);
        }
        return this->LLVMPtrType;
    }

    std::string ClassDeclNode::getQualifiedClassName() {
        return this->className;
    }

    unsigned int ClassDeclNode::getVariableIndex(std::string name) {

        int i = 0;
        for (VarDeclNode *ele:this->vars) {
            if (ele->getVariableName().compare(name) == 0) {
                return i;
            }
            i++;
        }
        // TODO this should be previous function line number
        throw new exceptions::SemanticException(
                "No member named '" + name + "' for the class '" + this->className + "'",
                this->lineNumber
        );

    }
}