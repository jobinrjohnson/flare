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
        return this->codeGenThrowE(cxt);
    }

    return nullptr;
}

flare::ast::StatementNode::StatementNode(flare::ast::StatementType type, Node *node) {
    this->type = type;
    this->operands.push_back(node);
}

llvm::Value *StatementNode::codeGenThrowE(Context *cxt) {

    // TODO this properly

    GlobalVariable *gvar = new llvm::GlobalVariable(
            *module,
            builder.getInt8PtrTy(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            0,
            "_ZTIi");
    gvar->setDSOLocal(true);

    //
    //
    //
    // __cxa_allocate_exception
    constexpr size_t numParams = 1;
    Type *returnType = cxt->getBuilder()->getVoidTy();
    Type *paramTypes[numParams] = {cxt->getBuilder()->getInt64Ty()};
    FunctionType *funcType = FunctionType::get(cxt->getBuilder()->getInt8PtrTy(),
                                               ArrayRef<Type *>(paramTypes, paramTypes + numParams),
                                               false /*isVariadic*/);
    Function *__cxa_allocate_exception = Function::Create(
            funcType, Function::ExternalLinkage, "__cxa_allocate_exception", *module);
    __cxa_allocate_exception->setDSOLocal(true);
    __cxa_allocate_exception->addFnAttr(Attribute::AttrKind::NoUnwind);

//    //
//    //
//    //
//    //
//    // __cxa_free_exception
//    Type *paramTypes2[numParams] = {cxt->getBuilder()->getVoidTy()};
//    FunctionType *funcType2 = FunctionType::get(returnType,
//                                                ArrayRef<Type *>(paramTypes2, paramTypes2 + numParams),
//                                                false /*isVariadic*/);
//    Function *__cxa_free_exception = Function::Create(
//            funcType2, Function::ExternalLinkage, "__cxa_free_exception", *module);
//    __cxa_free_exception->setDSOLocal(true);
//    __cxa_free_exception->addFnAttr(Attribute::AttrKind::NoUnwind);

    //
    //
    //
    //
    // __cxa_throw
    constexpr size_t numParams3 = 3;
    Type *paramTypes3[numParams3] = {
            cxt->getBuilder()->getInt8PtrTy(),
            cxt->getBuilder()->getInt8PtrTy(),
            cxt->getBuilder()->getInt8PtrTy()
    };
    FunctionType *funcType3 = FunctionType::get(returnType,
                                                ArrayRef<Type *>(paramTypes3, paramTypes3 + numParams3),
                                                false /*isVariadic*/);
    Function *__cxa_throw = Function::Create(
            funcType3, Function::ExternalLinkage, "__cxa_throw", *module);
    __cxa_throw->setDSOLocal(true);


    Value *params[1];
    params[0] = ConstantInt::get(cxt->getBuilder()->getInt64Ty(), 4);
    auto exception = cxt->getBuilder()->CreateCall(__cxa_allocate_exception,
                                                   ArrayRef<Value *>(params, params + 1));

    cxt->getBuilder()->CreateCall(__cxa_throw, {
            exception,
            builder.CreateBitCast(module->getGlobalVariable("_ZTIi"), builder.getInt8PtrTy()),
            ConstantPointerNull::get(builder.getInt8PtrTy())
    })->setDoesNotReturn();
    return builder.CreateUnreachable();

//    auto funType = FunctionType::get(
//            builder.getInt8PtrTy(),
//            None,
//            false
//    );
//    auto function = module->getOrInsertFunction("__FLARE_createUnWindException", funType);
//
//    auto funType2 = FunctionType::get(
//            builder.getVoidTy(),
//            {builder.getInt8PtrTy()},
//            false
//    );
//    auto raiseOurException = module->getOrInsertFunction("__FLARE_raiseException", funType2);
//    auto exception = builder.CreateCall(function, None, "getException");
//    builder.CreateCall(raiseOurException, exception);
//
//    return builder.CreateRet(ConstantInt::get(*cxt->getLLVMContext(), APInt(64, 0)));
}
