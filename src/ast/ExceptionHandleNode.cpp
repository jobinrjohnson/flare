//
// Created by jobinrjohnson on 27/06/21.
//

#include "ExceptionHandleNode.h"
#include <ast/FunctionNode.h>

namespace flare::ast {
    NodeType ExceptionHandleNode::getNodeType() {
        return NodeType::EXCEPTION_HANDLE_NODE;
    }

    llvm::Value *ExceptionHandleNode::codeGen(Context *cxt) {

//        FunctionNode *function = cxt->getCurrentFunction();
//
//        auto landingPadBlock = llvm::BasicBlock::Create(*cxt->getLLVMContext(),
//                                                        "landingPad",
//                                                        function->getLLVMFunctionRef()
//        );
//
//        builder.CreateBr(landingPadBlock);
//        cxt->getBuilder()->SetInsertPoint(landingPadBlock);
        return this->tryBlock->codeGen(cxt);
    }

    ExceptionHandleNode::ExceptionHandleNode(StatementListNode *tryBlock) {
        this->tryBlock = tryBlock;
    }

    void ExceptionHandleNode::addCatchBlock(StatementListNode *catchBlock, VarType *type) {
        this->catchBlocks.insert(std::pair<VarType *, StatementListNode *>(type, catchBlock));
    }
}
