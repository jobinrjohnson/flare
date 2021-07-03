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

        cxt->getCurrentFunction()->pushExceptionHandler(this);

        // Unwind block for invoke
        this->exceptionBlock = llvm::BasicBlock::Create(context,
                                                        "exception",
                                                        cxt->getCurrentFunction()->getLLVMFunctionRef());

        this->tryBlock->codeGen(cxt);

        cxt->getCurrentFunction()->popExceptionHandler();

        auto currentBlk = cxt->getBuilder()->GetInsertBlock();

        builder.SetInsertPoint(exceptionBlock);
        builder.CreateRet(llvm::ConstantInt::get(context, APInt(64, 1)));
        builder.SetInsertPoint(currentBlk);

        return nullptr;
    }

    ExceptionHandleNode::ExceptionHandleNode(StatementListNode *tryBlock) {
        this->tryBlock = tryBlock;
    }

    void ExceptionHandleNode::addCatchBlock(StatementListNode *catchBlock, VarType *type) {
        this->catchBlocks.insert(std::pair<VarType *, StatementListNode *>(type, catchBlock));
    }

    llvm::Value *
    ExceptionHandleNode::handleOperation(Context *cxt,
                                         std::function<llvm::Value *(BasicBlock *, BasicBlock *)> closure) {
        auto nb = BasicBlock::Create(
                context,
                "normal",
                cxt->getCurrentFunction()->getLLVMFunctionRef()
        );
        llvm::Value *val = closure(nb, this->exceptionBlock);
        builder.SetInsertPoint(nb);
        return val;
    }
}
