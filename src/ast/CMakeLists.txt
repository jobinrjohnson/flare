include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_library(
        ast
        STATIC

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
        implementation/StatementNode.cpp StatementNode.h helpers/Context.cpp helpers/Context.h implementation/FunctionNode.cpp FunctionNode.h implementation/LoopNode.cpp LoopNode.h)