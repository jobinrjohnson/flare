add_library(
        ast
        STATIC

        constants/AstConstants.h
        helpers/VariableHelper.h helpers/VariableHelper.cpp
        helpers/Context.cpp helpers/Context.h

        implementation/Node.cpp Node.h
        implementation/ExprNode.cpp ExprNode.h
        implementation/LiteralNode.cpp LiteralNode.h
        implementation/StatementListNode.cpp StatementListNode.h
        implementation/VarDeclNode.cpp VarDeclNode.h
        implementation/VariableDerefNode.cpp VariableDerefNode.h
        implementation/AssignmentNode.cpp AssignmentNode.h
        implementation/IfStatementNode.cpp IfStatementNode.h
        implementation/LogSmtNode.cpp LogSmtNode.h
        implementation/ValuePlaceholderNode.cpp ValuePlaceholderNode.h
        implementation/StatementNode.cpp StatementNode.h
        implementation/FunctionNode.cpp FunctionNode.h
        implementation/LoopNode.cpp LoopNode.h
        implementation/FunctionCallNode.cpp FunctionCallNode.h
        implementation/ClassDeclNode.cpp ClassDeclNode.h
)