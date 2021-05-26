%{

#include "parser.hh"
#include "scanner.h"
#include "driver.h"
#include "scanner-helper.h"

%}

%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="Lang"

%%

%{
  STEP();
%}

[a-zA-Z_]([a-zA-Z_]|[0-9])*             { return filterKwOrId(yylval, yytext, driver); }

[0-9]+                                  {
                                            yylval->tIntegerValue = atoi(yytext);
                                            return token::T_INTEGER;
                                        }

[0-9]+(\.[0-9][0-9]?)                   {
                                            yylval->tDecimalValue = atof(yytext);
                                            return token::T_DECIMAL;
                                        }

"+"                                     { return '+'; }
"-"                                     { return '-'; }
"*"                                     { return '*'; }
"/"                                     { return '/'; }
"%"                                     { return '%'; }
"="                                     { return '='; }
"<"                                     { return '<'; }
">"                                     { return '>'; }
"!"                                     { return '!'; }
">="                                    { return token::TOK_GTE; }
"<="                                    { return token::TOK_LTE; }
"=="                                    { return token::TOK_EQUALITY; }
"!="                                    { return token::TOK_NEQUALITY; }

"{"                                     { return '{'; }
"}"                                     { return '}'; }

"("                                     { return '('; }
")"                                     { return ')'; }

"["                                     { return '['; }
"]"                                     { return ']'; }



"."                                     { return '.'; }
","                                     { return ','; }
";"                                     { return ';'; }
":"                                     { return ':'; }

\"(\\.|[^"\\])*\"                       { return processString(yylval, yytext, driver); }




[ \t]+                                  STEP();

[\n\r]+                                 {
                                            STEP();
                                            LINE(1);
                                        }

"//".*                                  { /* Comment do nothing */ }

.                                       { processUnexpected(yylval, yytext, driver); }

%%

namespace lang {

    Scanner::Scanner() : LangFlexLexer() {}

    Scanner::~Scanner() {}

    void Scanner::setDebug(bool b) { yy_flex_debug = b; }

} // namespace lang

int LangFlexLexer::yylex()
{
  // TODO handle this properly
  std::cerr << "call langFlexLexer::yylex()!" << std::endl;
  throw "Lexer returned some errors";
  return 0;
}
