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

        llvm::Value *codeGen() {
            std::cout << "Calling VarDeclNode@codegen" << "\n";

            llvm::GlobalVariable *gvar_ptr_abc = new llvm::GlobalVariable(
                    *modules,
                    llvm::Type::getInt32Ty(llvmContext),
                    false,
                    llvm::GlobalValue::CommonLinkage,
                    0,
                    this->variableName);

            Value *value = this->initialValue->codeGen();
            gvar_ptr_abc->setInitializer(dyn_cast<Constant>(value));

            return gvar_ptr_abc;
        }

    };

}

#endif //FLARE_VARDECLNODE_H
