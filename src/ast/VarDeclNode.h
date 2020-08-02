//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_VARDECLNODE_H
#define FLARE_VARDECLNODE_H


#include "Node.h"

namespace ast {

    class VarDeclNode : public Node {

    protected:
        std::string variableName;

    public:

        VarDeclNode(char *name) {
            this->variableName.assign(name);
        }

        llvm::Value *codeGen() {
            std::cout << "Calling VarDeclNode@codegen" << "\n";

            auto value = llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0));

            llvm::GlobalVariable *gvar_ptr_abc = new llvm::GlobalVariable(
                    *modules,
                    llvm::Type::getFloatTy(llvmContext),
                    false,
                    llvm::GlobalValue::CommonLinkage,
                    0,
                    this->variableName);
            gvar_ptr_abc->setInitializer(value);

            return gvar_ptr_abc;
        }

    };

}

#endif //FLARE_VARDECLNODE_H
