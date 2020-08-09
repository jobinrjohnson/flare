include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_library(
        ast
        STATIC
        Node.h Node.cpp
        ExprNode.cpp ExprNode.h LiteralNode.cpp LiteralNode.h StatementListNode.cpp StatementListNode.h VarDeclNode.cpp VarDeclNode.h VariableDerefNode.cpp VariableDerefNode.h AssignmentNode.cpp AssignmentNode.h IfStatementNode.cpp IfStatementNode.h LogSmtNode.cpp LogSmtNode.h)