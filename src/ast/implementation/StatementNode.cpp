//
// Created by jobinrjohnson on 9/23/20.
//

#include <ast/helpers/VariableHelper.h>
#include <ast/StatementNode.h>
#include <ast/FunctionNode.h>

llvm::Value *flare::ast::StatementNode::codeGen(Context *cxt) {

    if (this->type == RETURN) {
        Value *operand = this->operands[0]->codeGen(cxt);

        Node *functionNode = cxt->getCurrentFunction();
        if (functionNode == nullptr) {
            throw "return should be inside a function";
        }
        return dynamic_cast<FunctionNode *>(functionNode)
                ->setFunctionReturn(operand);
    } else if (this->type == StatementType::THROW) {
        auto funType = FunctionType::get(
                builder.getInt32Ty(),
                None,
                false
        );
        auto function = module->getOrInsertFunction("__FLARE_throwException", funType);
        builder.CreateCall(function, None, "raiseException");
        return builder.CreateUnreachable();
    }

    return nullptr;
}

flare::ast::StatementNode::StatementNode(flare::ast::StatementType type, Node *node) {
    this->type = type;
    this->operands.push_back(node);
}
