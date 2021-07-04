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
        // Exception block
        builder.SetInsertPoint(exceptionBlock);


        auto extBlock = llvm::BasicBlock::Create(context,
                                                 "external",
                                                 cxt->getCurrentFunction()->getLLVMFunctionRef());


        // Create LLVM struct type for exception
        std::vector<llvm::Type *> items;
        items.push_back(builder.getInt8PtrTy());
        items.push_back(builder.getInt32Ty());
        static llvm::StructType *exceptionCaughtType = llvm::StructType::get(context,
                                                                             items);

        llvm::LandingPadInst *caughtResult = builder.CreateLandingPad(
                exceptionCaughtType,
                1,
                "exception_info"
        );
        caughtResult->setCleanup(true);

        llvm::Value *caughtResultStorage = new AllocaInst(exceptionCaughtType, 0, "s",
                                                          cxt->getBuilder()->GetInsertBlock());

        builder.CreateStore(caughtResult, caughtResultStorage);
        // TODO add catch handling cases

        // Exit block in case of no handler
        builder.CreateBr(extBlock);
        builder.SetInsertPoint(extBlock);
        builder.CreateResume(builder.CreateLoad(caughtResultStorage));


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
