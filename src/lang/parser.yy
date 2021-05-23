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

    #include "ast/constants/AstConstants.h"

    #include "ast/Node.h"
    #include "ast/ExprNode.h"
    #include "ast/LiteralNode.h"
    #include "ast/StatementListNode.h"
    #include "ast/StatementNode.h"
    #include "ast/VariableDerefNode.h"
    #include "ast/AssignmentNode.h"
    #include "ast/IfStatementNode.h"
    #include "ast/LogSmtNode.h"
    #include "ast/FunctionNode.h"
    #include "ast/FunctionCallNode.h"
    #include "ast/LoopNode.h"
    #include "ast/ClassDeclNode.h"

    // Namespace
    using namespace flare::ast;
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
    Node *node;
    LiteralNode *literal;
    ExprNode *expression;
    StatementListNode *statementList;
    VarDeclNode *varDecl;
    AssignmentNode *assignmentNode;
    IfStatementNode *ifStatementNode;
    LogSmtNode *logSmtNode;
    StatementNode *statementNode;
    FunctionNode *functionNode;
    FunctionCallNode *functionCallNode;
    LoopNode *loopNode;
    Parameter *parameter;
    std::vector<Parameter *> *parameterList;
    std::vector<ExprNode *> *arguments;
    VarType *varType;
    ClassDeclNode *classDeclNode;
    std::vector<Node *> *nodeList;

    int tIntegerValue;
    bool tBoolValue;
    double tDecimalValue;
    char *tStringValue;
    char *yyText;
}


%start start


%type <statementList> start
%type <node> statement class_content
%type <expression> expr
%type <literal> scalar
%type <statementList> compound_statement statements
%type <varDecl> variable_declaration array_declaration
%type <assignmentNode> assignment_expr
%type <ifStatementNode> if_else_if if_statement
%type <logSmtNode> log_statement
%type <statementNode> return_statement
%type <functionNode> function_declaration
%type <loopNode> loops
%type <functionCallNode> function_call
%type <parameterList> parameter_list
%type <parameter> parameter
%type <arguments> arguments
%type <varType> var_type
%type <classDeclNode> class_decl
%type <nodeList> class_contents

%token <yyText> IDENTIFIER
%token <tIntegerValue> T_INTEGER
%token <tDecimalValue> T_DECIMAL
%token <tBoolValue> T_BOOLEAN
%token <tStringValue> T_STRING
%token TOK_EOF 0 PLUS KW_LET KW_IF KW_ELSE KW_LOG KW_CONSOLE KW_RETURN KW_FUNCTION KW_WHILE KW_CLASS
%token TOK_LTE TOK_GTE TOK_EQUALITY TOK_NEQUALITY
%token KW_INT KW_INT32 KW_INT64 KW_NUMBER KW_FLOAT KW_DOUBLE KW_BIGINT KW_BOOLEAN

%precedence '=' 
%left '|'
%left '^'
%left '&'
%nonassoc TOK_EQUALITY TOK_NEQUALITY
%nonassoc '<' TOK_LTE '>' TOK_GTE
%left '.'
%left '+' '-'
%left '*' '/' '%'
%precedence '!'

%%

start:
    statements  {

        $$ = $1;
        $$->startCodeGen();

    }
;

statements:
    statements statement             { $1->push($<node>2); $$ = $1; }
    |                                { $$ = new StatementListNode();  }
;


statement:
    expr                                { $$->setLineNumber(driver.cursor->end.line); }
    | variable_declaration              { $$->setLineNumber(driver.cursor->end.line); }
    | assignment_expr                   { $$->setLineNumber(driver.cursor->end.line); }
    | if_else_if                        { $$->setLineNumber(driver.cursor->end.line); }
    | log_statement                     { $$->setLineNumber(driver.cursor->end.line); }
    | return_statement                  { $$->setLineNumber(driver.cursor->end.line); }
    | statement ';'                     { $$ = $1; }
    | function_declaration              { $$->setLineNumber(driver.cursor->end.line); }
    | loops                             { $$->setLineNumber(driver.cursor->end.line); }
    | class_decl                        { $$->setLineNumber(driver.cursor->end.line); }
    | compound_statement                { $$->setLineNumber(driver.cursor->begin.line); }
;

compound_statement:
    '{' statements '}'                { $$ = $2; }
;

class_content:
    function_declaration                {}
    | variable_declaration              {}
    |                                   {}
;

class_contents:
    class_content                     {
        $$ = new std::vector<Node *>();
        $$->push_back($1);
    }
    | class_contents class_content        { $1->push_back($2); $$ = $1; }
;

class_decl:
    KW_CLASS IDENTIFIER '{' class_contents '}'      { $$ = new ClassDeclNode($2, $4); free($4); }
;

loops:
    KW_WHILE '(' expr ')' compound_statement    { $$ = new LoopNode($3, $5);}
;

function_declaration:
    KW_FUNCTION IDENTIFIER '(' ')' ':' var_type compound_statement   { $$ = new FunctionNode($2, $<statementList>7, $6); }
    | KW_FUNCTION IDENTIFIER '(' parameter_list ')' ':' var_type compound_statement   { $$ = new FunctionNode($2, $<statementList>8, $7, $4); }
;

parameter:
    IDENTIFIER ':' var_type                    { $$ = new Parameter($1, $3); }
;

parameter_list:
    parameter                                  {
        $$ = new std::vector<Parameter *>();
        $$->push_back($1);
    }
    | parameter_list ',' parameter             { $1->push_back($3); $$ = $1; }
;

log_statement:
    KW_CONSOLE '.' KW_LOG '(' expr ')'  {  $$ = new LogSmtNode($<node>5);  }
;

return_statement:
    // TODO return void
    KW_RETURN expr                      { $$ = new StatementNode(StatementType::RETURN, $<node>2); }
;

if_statement:
    KW_IF '(' expr ')' statement                           {
        $$ = new IfStatementNode($3, $5);
    }
    | if_statement KW_ELSE if_statement                                  { $1->addBranch($3); $$ = $1; }
;

if_else_if:
    if_statement                                            {}
    | if_statement KW_ELSE statement                         {
        $1->addElseBranch($3);
        $$ = $1;
    }
;

variable_declaration:
    array_declaration                       { }
    | KW_LET IDENTIFIER                     { $$ = new VarDeclNode($2); free($2);  }
    | KW_LET IDENTIFIER ':' var_type        { $$ = new VarDeclNode($2, $4); free($2); }
    | variable_declaration '=' expr         { $$->setInitialValue($3); }
;

var_type:
    KW_INT              { $$ = new VarType; $$->type = VARTYPE_INT; }
    | KW_INT32          { $$ = new VarType; $$->type = VARTYPE_INT_32; }
    | KW_INT64          { $$ = new VarType; $$->type = VARTYPE_INT_64; }
    | KW_BIGINT         { $$ = new VarType; $$->type = VARTYPE_INT_64; }
    | KW_NUMBER         { $$ = new VarType; $$->type = VARTYPE_NUMBER; }
    | KW_FLOAT          { $$ = new VarType; $$->type = VARTYPE_FLOAT; }
    | KW_DOUBLE         { $$ = new VarType; $$->type = VARTYPE_DOUBLE; }
    | KW_BOOLEAN         { $$ = new VarType; $$->type = VARTYPE_BOOLEAN; }
;

array_declaration:
    KW_LET IDENTIFIER '[' ']'           {
            VarType *vType = new VarType{
                    .type = VARTYPE_ARRAY,
                    .subType = VARTYPE_INT,
                    .name = "array"
            };
            $$ = new VarDeclNode($2, vType);
    }
;


assignment_expr:
    IDENTIFIER '=' expr                         { $$ = new AssignmentNode($1, $3); free($1); }
    | IDENTIFIER '[' expr ']' '=' expr          { $$ = new AssignmentNode($1, $3, $6); free($1); }
;

arguments:
    expr                                        {
        $$ = new std::vector<ExprNode *>();
        $$->push_back($1);
    }
    | arguments ',' expr                        { $1->push_back($3); $$=$1; }
;

function_call:
    IDENTIFIER '(' ')'                          { $$ = new FunctionCallNode($1); }
    | IDENTIFIER '(' arguments ')'              { $$ = new FunctionCallNode($1, $3); }
;


expr:
    scalar                          { $$ = new ExprNode(OperatorType::SCALAR, $1); }
    | function_call                 { $$ = new ExprNode(OperatorType::FUNCTION_CALL, $1); }
    | IDENTIFIER                    {
                                        auto derefrence = new VariableDerefNode($1);
                                        $$ = new ExprNode(OperatorType::VAR_DE_REF, derefrence);
                                    }
    | IDENTIFIER '[' expr ']'       {
                                        auto derefrence = new VariableDerefNode($1, $3);
                                        $$ = new ExprNode(OperatorType::VAR_DE_REF, derefrence);
                                    }
    | '(' expr ')'                  { $$ = new ExprNode(OperatorType::GROUPED, $2); }
    | '+' expr                      { $$ = new ExprNode(OperatorType::UNARY_PLUS, $2); }
    | '-' expr                      { $$ = new ExprNode(OperatorType::UNARY_MINUS, $2); }
    | expr '+' expr                 { $$ = new ExprNode(OperatorType::PLUS, $1, $3); }
    | expr '-' expr                 { $$ = new ExprNode(OperatorType::MINUS, $1, $3); }
    | expr '*' expr                 { $$ = new ExprNode(OperatorType::MUL, $1, $3); }
    | expr '/' expr                 { $$ = new ExprNode(OperatorType::DIV, $1, $3); }
    | expr '%' expr                 { $$ = new ExprNode(OperatorType::MODULO_DIV, $1, $3); }
    | expr '<' expr                 { $$ = new ExprNode(OperatorType::LESS_THAN, $1, $3); }
    | expr '>' expr                 { $$ = new ExprNode(OperatorType::GREATER_THAN, $1, $3); }
    | expr TOK_LTE expr             { $$ = new ExprNode(OperatorType::LESS_THAN_EQUAL, $1, $3); }
    | expr TOK_GTE expr             { $$ = new ExprNode(OperatorType::GREATER_THAN_EQUAL, $1, $3); }
    | expr TOK_EQUALITY expr        { $$ = new ExprNode(OperatorType::EQUALITY, $1, $3); }
    | expr TOK_NEQUALITY expr       { $$ = new ExprNode(OperatorType::NOT_EQUALITY, $1, $3); }
    | '!' expr                      { $$ = new ExprNode(OperatorType::NOT, $2); }
;


scalar:
    T_INTEGER                           { $$ = new LiteralNode($1); }
    | T_DECIMAL                         { $$ = new LiteralNode($1); }
    | T_BOOLEAN                         { $$ = new LiteralNode($1); }
    | T_STRING                          { $$ = new LiteralNode($1); }
;

%%

namespace lang {
    void Parser::error(const location &, const std::string &m) {
      // TODO handle this properly
      std::cerr << *driver.cursor << ": " << m << std::endl;
      driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
      throw "Some syntax errors";
    }
} // namespace lang