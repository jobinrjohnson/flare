//
// Created by jobinrjohnson on 27/06/21.
//

#include "ExceptionHandleNode.h"
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

    llvm::Value *ExceptionHandleNode::codeGen2(Context *cxt) {

        cxt->getCurrentFunction()->pushExceptionHandler(this);

        // Unwind block for invoke
        this->exceptionBlock = llvm::BasicBlock::Create(context,
                                                        "exception",
                                                        cxt->getCurrentFunction()->getLLVMFunctionRef());

        auto extBlock = llvm::BasicBlock::Create(context,
                                                 "external",
                                                 cxt->getCurrentFunction()->getLLVMFunctionRef());

        this->tryBlock->codeGen(cxt);

        cxt->getCurrentFunction()->popExceptionHandler();

        auto currentBlk = cxt->getBuilder()->GetInsertBlock();
        // Exception block
        builder.SetInsertPoint(exceptionBlock);


        // Create LLVM struct type for exception
        std::vector<llvm::Type *> items;
        items.push_back(builder.getInt8PtrTy());
        items.push_back(builder.getInt32Ty());
        static llvm::StructType *exceptionCaughtType = llvm::StructType::get(context,
                                                                             items);


        llvm::LandingPadInst *landingPad = builder.CreateLandingPad(
                exceptionCaughtType,
                1,
                "exception_info"
        );
//        landingPad->setCleanup(true);


//        new llvm::GlobalVariable(
//                *module,
//                builder.getInt8PtrTy(),
//                false,
//                llvm::GlobalValue::InternalLinkage,
//                0);

//        GlobalVariable *gvar =
//                new GlobalVariable(*module, builder.getInt8PtrTy(), true,
//                                                  GlobalVariable::ExternalLinkage, 0, "global_exception");
//gvar->setDSOLocal(true);
//        module->getOrInsertGlobal("global_exception", builder.getInt64Ty());
//        GlobalVariable *gv = module->getGlobalVariable("global_exception", true);
//        gv->setLinkage(GlobalVariable::ExternalLinkage);


        landingPad->addClause(module->getGlobalVariable("global_exception", true));
//        landingPad->addClause(module->getGlobalVariable("global_exception", true));


        llvm::Value *caughtResultStorage = new AllocaInst(
                builder.getInt8PtrTy(),
                0,
                "stored_exception",
                cxt->getBuilder()->GetInsertBlock()
        );
//
        builder.CreateStore(builder.CreateExtractValue(landingPad, 0), caughtResultStorage);
        // TODO add catch handling cases
        builder.CreateBr(extBlock);


        builder.SetInsertPoint(extBlock);
        this->catchBlocks.begin()->second->codeGen(cxt);
        builder.CreateBr(cxt->getCurrentFunction()->getExitBlock(cxt));

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
