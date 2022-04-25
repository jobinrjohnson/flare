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
        this->printCallStack(cxt, "ExceptionHandleNode", __FUNCTION__);

        // Add personality block
        cxt->getCurrentFunction()->setPersonalityFunction(cxt->getPersonalityFunction());

        // Unwind block for invoke
        this->exceptionBlock = BasicBlock::Create(
                context,
                "exception",
                cxt->getCurrentFunction()->getLLVMFunctionRef()
        );

        // finally block
        BasicBlock *afterExceptionBlock = BasicBlock::Create(
                context,
                "afterExceptionBlock",
                cxt->getCurrentFunction()->getLLVMFunctionRef()
        );

        // try block
        cxt->getCurrentFunction()->pushExceptionHandler(this);
        this->tryBlock->codeGen(cxt->next());
        cxt->getCurrentFunction()->popExceptionHandler();

        // Ending last normal block
        if (cxt->getBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
            cxt->getBuilder()->CreateBr(afterExceptionBlock);
        }

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
        auto ptr = builder.CreateBitCast(module->getGlobalVariable("_ZTIi"), builder.getInt8PtrTy());
        caughtResult->addClause(static_cast<Constant *>(ptr));

        // TODO properly
        this->catchBlocks.begin()->second->codeGen(cxt->next());

        // TODO properly
        if (this->finallyNode != nullptr && exceptionBlock->getTerminator() == nullptr)
            this->finallyNode->codeGen(cxt->next());

        if (exceptionBlock->getTerminator() == nullptr) {
            builder.CreateBr(afterExceptionBlock);
        }
        //
        //
        //

        builder.SetInsertPoint(afterExceptionBlock);

        return nullptr;

    }

    ExceptionHandleNode::ExceptionHandleNode(StatementListNode *tryBlock) {
        this->tryBlock = tryBlock;
    }

    void ExceptionHandleNode::addCatchBlock(StatementListNode *catchBlock, VarType *type, std::string varName) {
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

    void ExceptionHandleNode::setFinallyBlock(StatementListNode *finallyStatementListNode) {
        this->finallyNode = finallyStatementListNode;
    }
}
