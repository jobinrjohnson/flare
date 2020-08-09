%{
#include "parser.hh"
#include "scanner.h"

#define yylex driver.scanner->yylex
%}

%code requires
{
    #include "driver.h"
    #include "location.hh"
    #include <iostream>

    #include"../ast/Node.h"
    #include"../ast/ExprNode.h"
    #include"../ast/LiteralNode.h"
    #include"../ast/StatementListNode.h"
    #include"../ast/VariableDerefNode.h"
    #include"../ast/AssignmentNode.h"
    #include"../ast/IfStatementNode.h"

}

%code provides
{
    namespace lang {
        class Driver;

        inline void yyerror(const char *msg) { std::cerr << msg << std::endl; }
    } // namespace lang
}

%require "3.4"
%language "C++"
%locations
%defines
%debug
%define api.namespace {lang}
%define api.parser.class {Parser}
%parse-param {Driver &driver}
%lex-param {Driver &driver}
%define parse.error verbose

%union
{
    ast::Node *node;
    ast::LiteralNode *literal;
    ast::ExprNode *expression;
    ast::StatementListNode *statementList;
    ast::VarDeclNode *varDecl;
    ast::AssignmentNode *assignmentNode;
    ast::IfStatementNode *ifStatementNode;

    int tIntegerValue;
    char *yyText;
}


%start start


%type <statementList> start
%type <expression> expr
%type <literal> scalar
%type <statementList> statements
%type <varDecl> variable_declaration
%type <assignmentNode> assignment_expr
%type <ifStatementNode> if_statement if_else_if


%token <yyText> IDENTIFIER
%token <tIntegerValue> T_INTEGER
%token TOK_EOF 0 PLUS KW_LET KW_VAR KW_IF KW_ELSE

%left '+' '-'
%left '*' '/' 

%%

start:
    '{' statements '}' {

        $$ = $2;
        $$->printLLVMir();

    }
;


statements:
    statement                           { $$ = new ast::StatementListNode($<node>1);  }
    | statements statement              { $1->push($<node>2); }
;

statement:
    expr                                { }
    | variable_declaration              { }
    | assignment_expr                   { }
    | if_statement                      { }
    | if_else_if                        { }
;

if_else_if:
    if_statement  KW_ELSE KW_IF '(' expr ')' '{' statements '}' {
        $1->addBranch($5, $8);
        $$ = $1;
    }
;

if_statement:
    KW_IF '(' expr ')' '{' statements '}'      {

            $$ = new ast::IfStatementNode($3, $6);

    }
;

variable_declaration:
    KW_LET IDENTIFIER                   { $$ = new ast::VarDeclNode($2); }
    | KW_VAR IDENTIFIER                 { $$ = new ast::VarDeclNode($2); }
    | KW_LET IDENTIFIER '=' expr        { $$ = new ast::VarDeclNode($2, $4); free($2); }
    | KW_VAR IDENTIFIER '=' expr        { $$ = new ast::VarDeclNode($2, $4); free($2); }
;

assignment_expr:
    IDENTIFIER '=' expr                 { $$ = new ast::AssignmentNode($1, $3); free($1); }
;


expr:
    scalar                          { $$ = new ast::ExprNode(OperatorType::SCALAR, $1); }
    | IDENTIFIER                    {
                                        auto derefrence = new ast::VariableDerefNode($1);
                                        $$ = new ast::ExprNode(OperatorType::VAR_DE_REF, derefrence);
                                    }
    | expr '+' expr                 { $$ = new ast::ExprNode(OperatorType::PLUS, $1, $3); }
    | expr '-' expr                 { $$ = new ast::ExprNode(OperatorType::MINUS, $1, $3); }
    | expr '*' expr                 { $$ = new ast::ExprNode(OperatorType::MUL, $1, $3); }
    | expr '/' expr                 { $$ = new ast::ExprNode(OperatorType::DIV, $1, $3); }
    | expr '%' expr                 { $$ = new ast::ExprNode(OperatorType::MODE, $1, $3); }
    | expr '<' expr                 { $$ = new ast::ExprNode(OperatorType::LESS_THAN, $1, $3); }
;


scalar:
    T_INTEGER                         { $$ = new ast::LiteralNode($1); }
;

%%

namespace lang {
    void Parser::error(const location &, const std::string &m) {
      std::cerr << *driver.cursor << ": " << m << std::endl;
      driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
} // namespace lang