//
// Created by jobinrjohnson on 27/06/21.
//

#include "ast/ExceptionHandleNode.h"
#include <ast/FunctionNode.h>
#include "llvm/ADT/STLExtras.h"

namespace flare::ast {
    NodeType ExceptionHandleNode::getNodeType() {
        return NodeType::EXCEPTION_HANDLE_NODE;
    }


    llvm::Value *ExceptionHandleNode::codeGen(Context *cxt) {

        cxt->getCurrentFunction()->setPersonalityFunction(cxt->getPersonalityFunction());

        // Unwind block for invoke
        this->exceptionBlock = BasicBlock::Create(
                context,
                "exception",
                cxt->getCurrentFunction()->getLLVMFunctionRef()
        );

        // try block
        cxt->getCurrentFunction()->pushExceptionHandler(this);
        this->tryBlock->codeGen(cxt);
        cxt->getCurrentFunction()->popExceptionHandler();

        // Ending normal block
        // builder.CreateBr(cxt->getCurrentFunction()->getExitBlock(cxt));
        cxt->getCurrentFunction()->setFunctionReturn(ConstantInt::get(*cxt->getLLVMContext(), APInt(64, 1)));

        //
        //
        //
        // catch block
        builder.SetInsertPoint(exceptionBlock);
        std::vector<llvm::Type *> caughtResultFieldTypes = {
                builder.getInt8PtrTy(),
                builder.getInt32Ty()
        };
        llvm::StructType *ourCaughtResultType = llvm::StructType::get(context, caughtResultFieldTypes);
        LandingPadInst *caughtResult = builder.CreateLandingPad(
                ourCaughtResultType,
                1,
                "landingPad"
        );
        caughtResult->addClause(module->getGlobalVariable("_ZTIi"));

        this->catchBlocks.begin()->second->codeGen(cxt);

        if (exceptionBlock->getTerminator() == nullptr) {
            cxt->getCurrentFunction()->setFunctionReturn(ConstantInt::get(*cxt->getLLVMContext(), APInt(64, 1)));
        }
        //
        //
        //

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
