//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_VARDECLNODE_H
#define FLARE_VARDECLNODE_H


#include "Node.h"
#include "LiteralNode.h"

namespace ast {

    class VarDeclNode : public Node {

    protected:
        std::string variableName;
        Node *initialValue;

        bool isArray = false;

    public:

        NodeType getNodeType() {
            return VAR_DECL_NODE;
        }

        VarDeclNode(char *name, bool isArray = false) {
            this->variableName.assign(name);
            this->initialValue = new ast::LiteralNode(0);
            this->isArray = isArray;
        }

        VarDeclNode(char *name, Node *initialValue, bool isArray = false) {
            this->variableName = name;
            this->initialValue = initialValue;
            this->isArray = isArray;
        }

        llvm::Value *codeGen(int depth) {

            if (this->isArray) {

                std::vector<llvm::Constant *> initList;
                initList.push_back(ConstantInt::get(Type::getInt32Ty(context), 100));

                llvm::ArrayType *array = llvm::ArrayType::get(Type::getInt32Ty(context), 1);
                llvm::Constant *initializer = llvm::ConstantArray::get(array, initList);

                llvm::Value *unitInitList = new llvm::GlobalVariable(*module,
                                                                     array,
                                                                     false,
                                                                     llvm::GlobalValue::ExternalLinkage,
                                                                     initializer,
                                                                     this->variableName
                );

                return unitInitList;
            }


            this->printCallStack(depth, "VarDeclNode", __FUNCTION__);

            llvm::GlobalVariable *gvar = new llvm::GlobalVariable(
                    *module,
                    llvm::Type::getInt32Ty(context),
                    false,
                    llvm::GlobalValue::CommonLinkage,
                    0,
                    this->variableName);

            Value *value = this->initialValue->codeGen(depth + 1);
            gvar->setInitializer(dyn_cast<Constant>(value));

            return gvar;
        }

    };

}

#endif //FLARE_VARDECLNODE_H
