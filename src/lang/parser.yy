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

    #include"../ast/ExprNode.h"
    #include"../ast/LiteralNode.h"

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
    ast::ExprNode *ast;
    // Originals
    ast::LiteralNode *literal;
    ast::ExprNode *expression;
    int tIntegerValue;
}

%start start
%type <ast> start
%type <expression> expr
%type <literal> scalar


%token <tIntegerValue> T_INTEGER
%token TOK_EOF 0 PLUS IDENTIFIER

%left '+' '-'
%left '*' '/' 

%%

start:
    '{' expr '}' {

        $$ = $2;
        $$->printLLVMir();

    }
;

expr:
        scalar '+' scalar             { $$ = new ast::ExprNode(OperatorType::PLUS, $1, $3); }
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