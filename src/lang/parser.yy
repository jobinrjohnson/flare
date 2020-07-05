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
    ast::Node *ast;
    int tIntegerValue;
}

%start start
%type <ast> start expr scalar statements statement assignment_expression


%token <tIntegerValue> T_INTEGER
%token TOK_EOF 0 PLUS IDENTIFIER

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
    statement                       { $$ = $1; }
    | statement statements          { $$ = $1; }
;

statement:
    ';'                             { $$ = nullptr; }
    | expr ';'                      { $$ = $1; }
;


expr:
        expr '+' expr                   { $$ = new ast::Node('+', $1, $3);  }
        | assignment_expression         { $$ = $1; }
        | scalar                        { $$ = $1; }
;

assignment_expression:
        IDENTIFIER '=' expr             { }
;

scalar :
    T_INTEGER                           { $$ = new ast::Node($1); }
;

%%

namespace lang {
    void Parser::error(const location &, const std::string &m) {
      std::cerr << *driver.cursor << ": " << m << std::endl;
      driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
} // namespace lang