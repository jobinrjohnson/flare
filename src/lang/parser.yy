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

    int tIntegerValue;
    char *yyText;
}


%start start


%type <statementList> start
%type <expression> expr
%type <literal> scalar
%type <statementList> statements
%type <varDecl> variable_declaration


%token <yyText> IDENTIFIER
%token <tIntegerValue> T_INTEGER
%token TOK_EOF 0 PLUS KW_LET KW_VAR

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
;

variable_declaration:
    KW_LET IDENTIFIER                   { $$ = new ast::VarDeclNode($2); }
    | KW_VAR IDENTIFIER                 { $$ = new ast::VarDeclNode($2); }
;


expr:
        scalar                          { $$ = new ast::ExprNode(OperatorType::SCALAR, $1); }
        | expr '+' expr                 { $$ = new ast::ExprNode(OperatorType::PLUS, $1, $3); }
        | expr '-' expr                 { $$ = new ast::ExprNode(OperatorType::MINUS, $1, $3); }
        | expr '*' expr                 { $$ = new ast::ExprNode(OperatorType::MUL, $1, $3); }
        | expr '/' expr                 { $$ = new ast::ExprNode(OperatorType::DIV, $1, $3); }
        | expr '%' expr                 { $$ = new ast::ExprNode(OperatorType::MODE, $1, $3); }
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