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

        // Block which calls invoke
//        llvm::BasicBlock *entryBlock = llvm::BasicBlock::Create(context,
//                                                                "entry",
//                                                                cxt->getCurrentFunction()->getLLVMFunctionRef());
//        // Normal block for invoke
//        llvm::BasicBlock *normalBlock = llvm::BasicBlock::Create(context,
//                                                                 "normal",
//                                                                 cxt->getCurrentFunction()->getLLVMFunctionRef());
//        // Unwind block for invoke
//        llvm::BasicBlock *exceptionBlock = llvm::BasicBlock::Create(context,
//                                                                    "exception",
//                                                                    cxt->getCurrentFunction()->getLLVMFunctionRef());
//
//        llvm::Function *toPrint32Int = module.get()->getFunction("print32Int");
//
//
//
//        std::vector<llvm::Value*> args;
//        args.push_back(builder.CreateGlobalStringPtr(StringRef("hello %d"), "str"));
//        args.push_back(llvm::ConstantInt::get(context, APInt(64, 100)));
//        builder.CreateInvoke(toPrint32Int,
//                             normalBlock,
//                             exceptionBlock,
//                             args);



        return this->tryBlock->codeGen(cxt);
    }

    ExceptionHandleNode::ExceptionHandleNode(StatementListNode *tryBlock) {
        this->tryBlock = tryBlock;
    }

    void ExceptionHandleNode::addCatchBlock(StatementListNode *catchBlock, VarType *type) {
        this->catchBlocks.insert(std::pair<VarType *, StatementListNode *>(type, catchBlock));
    }
}
