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

    public:

        NodeType getNodeType() {
            return VAR_DECL_NODE;
        }

        VarDeclNode(char *name) {
            this->variableName.assign(name);
            this->initialValue = new ast::LiteralNode(0);
        }

        VarDeclNode(char *name, Node *initialValue) {
            this->variableName = name;
            this->initialValue = initialValue;
        }

        llvm::Value *codeGen(int depth) {
            this->printCallStack(depth,"VarDeclNode", __FUNCTION__);

            llvm::GlobalVariable *gvar = new llvm::GlobalVariable(
                    *modules,
                    llvm::Type::getInt32Ty(llvmContext),
                    false,
                    llvm::GlobalValue::CommonLinkage,
                    0,
                    this->variableName);

            Value *value = this->initialValue->codeGen(depth+1);
            gvar->setInitializer(dyn_cast<Constant>(value));

            return gvar;
        }

    };

}

#endif //FLARE_VARDECLNODE_H
