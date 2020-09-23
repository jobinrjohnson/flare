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

    #include "ast/Node.h"
    #include "ast/ExprNode.h"
    #include "ast/LiteralNode.h"
    #include "ast/StatementListNode.h"
    #include "ast/StatementNode.h"
    #include "ast/VariableDerefNode.h"
    #include "ast/AssignmentNode.h"
    #include "ast/IfStatementNode.h"
    #include "ast/LogSmtNode.h"

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
    ast::LogSmtNode *logSmtNode;
    ast::StatementNode *statementNode;

    int tIntegerValue;
    double tDecimalValue;
    char *yyText;
}


%start start


%type <statementList> start
%type <expression> expr
%type <literal> scalar
%type <statementList> statements
%type <varDecl> variable_declaration array_declaration
%type <assignmentNode> assignment_expr
%type <ifStatementNode> if_else_if
%type <logSmtNode> log_statement
%type <statementNode> return_statement


%token <yyText> IDENTIFIER
%token <tIntegerValue> T_INTEGER
%token <tDecimalValue> T_DECIMAL
%token TOK_EOF 0 PLUS KW_LET KW_VAR KW_IF KW_ELSE KW_LOG KW_RETURN
%token TOK_LTE TOK_GTE TOK_EQUALITY TOK_NEQUALITY

%left '+' '-'
%left '*' '/' '%'

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
    | if_else_if                        { }
    | log_statement                     { }
    | return_statement                  { }
;

log_statement:
    KW_LOG '(' expr ')'                 {  $$ = new ast::LogSmtNode($<node>3);  }
;

return_statement:
    // TODO return void
    KW_RETURN expr                      { $$ = new ast::StatementNode(ast::StatementType::RETURN, $<node>2); }
;


if_else_if:
    KW_IF '(' expr ')' '{' statements '}'                           {
        $$ = new ast::IfStatementNode($3, $6);
    }
    | if_else_if KW_ELSE KW_IF '(' expr ')' '{' statements '}'      {
        $1->addBranch($5, $8);
        $$ = $1;
    }
    | if_else_if KW_ELSE '{' statements '}'                         {
        $1->addElseBranch($4);
        $$ = $1;
    }
;

variable_declaration:
    array_declaration                   { }
    | KW_LET IDENTIFIER                 { $$ = new ast::VarDeclNode($2); }
    | KW_VAR IDENTIFIER                 { $$ = new ast::VarDeclNode($2); }
    | KW_LET IDENTIFIER '=' expr        { $$ = new ast::VarDeclNode($2, $4); free($2); }
    | KW_VAR IDENTIFIER '=' expr        { $$ = new ast::VarDeclNode($2, $4); free($2); }
;

array_declaration:
    KW_LET IDENTIFIER '[' ']'           { $$ = new ast::VarDeclNode($2, true); }
;


assignment_expr:
    IDENTIFIER '=' expr                         { $$ = new ast::AssignmentNode($1, $3); free($1); }
    | IDENTIFIER '[' expr ']' '=' expr          { $$ = new ast::AssignmentNode($1, $3, $6); free($1); }
;


expr:
    scalar                          { $$ = new ast::ExprNode(OperatorType::SCALAR, $1); }
    | IDENTIFIER                    {
                                        auto derefrence = new ast::VariableDerefNode($1);
                                        $$ = new ast::ExprNode(OperatorType::VAR_DE_REF, derefrence);
                                    }
    | IDENTIFIER '[' expr ']'       {
                                        auto derefrence = new ast::VariableDerefNode($1, $3);
                                        $$ = new ast::ExprNode(OperatorType::VAR_DE_REF, derefrence);
                                    }
    | '(' expr ')'                  { $$ = new ast::ExprNode(OperatorType::GROUPED, $2); }
    | '+' expr                      { $$ = new ast::ExprNode(OperatorType::UNARY_PLUS, $2); }
    | '-' expr                      { $$ = new ast::ExprNode(OperatorType::UNARY_MINUS, $2); }
    | expr '+' expr                 { $$ = new ast::ExprNode(OperatorType::PLUS, $1, $3); }
    | expr '-' expr                 { $$ = new ast::ExprNode(OperatorType::MINUS, $1, $3); }
    | expr '*' expr                 { $$ = new ast::ExprNode(OperatorType::MUL, $1, $3); }
    | expr '/' expr                 { $$ = new ast::ExprNode(OperatorType::DIV, $1, $3); }
    | expr '%' expr                 { $$ = new ast::ExprNode(OperatorType::MODULO_DIV, $1, $3); }
    | expr '<' expr                 { $$ = new ast::ExprNode(OperatorType::LESS_THAN, $1, $3); }
    | expr '>' expr                 { $$ = new ast::ExprNode(OperatorType::GREATER_THAN, $1, $3); }
    | expr TOK_LTE expr             { $$ = new ast::ExprNode(OperatorType::LESS_THAN_EQUAL, $1, $3); }
    | expr TOK_GTE expr             { $$ = new ast::ExprNode(OperatorType::GREATER_THAN_EQUAL, $1, $3); }
    | expr TOK_EQUALITY expr        { $$ = new ast::ExprNode(OperatorType::EQUALITY, $1, $3); }
    | expr TOK_NEQUALITY expr       { $$ = new ast::ExprNode(OperatorType::NOT_EQUALITY, $1, $3); }
    | '!' expr                      { $$ = new ast::ExprNode(OperatorType::NOT, $2); }
;


scalar:
    T_INTEGER                         { $$ = new ast::LiteralNode($1); }
    | T_DECIMAL                       { $$ = new ast::LiteralNode($1); }
;

%%

namespace lang {
    void Parser::error(const location &, const std::string &m) {
      std::cerr << *driver.cursor << ": " << m << std::endl;
      driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
} // namespace lang