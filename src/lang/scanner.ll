%{

#include "parser.hh"
#include "scanner.h"
#include "driver.h"


#define STEP()                                                                 \
  do {                                                                         \
    driver.cursor->step();                                                     \
  } while (0)

#define COL(Col) driver.cursor->columns(Col)

#define LINE(Line)                                                             \
  do {                                                                         \
    driver.cursor->lines(Line);                                                \
  } while (0)

#define YY_USER_ACTION COL(yyleng);

typedef lang::Parser::token token;
typedef lang::Parser::token_type token_type;

#define yyterminate() return token::TOK_EOF

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

[a-zA-Z_]([a-zA-Z_]|[0-9])* {

                if (strcmp("let", yytext) == 0) {
                    return token::KW_LET;
                } else if (strcmp("var", yytext) == 0) {
                    return token::KW_VAR;
                } else if (strcmp("if", yytext) == 0) {
                    return token::KW_IF;
                } else if (strcmp("else", yytext) == 0) {
                    return token::KW_ELSE;
                }else if (strcmp("log", yytext) == 0) {
                    return token::KW_LOG;
                }else if (strcmp("return", yytext) == 0) {
                    return token::KW_RETURN;
                }else if (strcmp("function", yytext) == 0) {
                    return token::KW_FUNCTION;
                }else if (strcmp("console", yytext) == 0) {
                    return token::KW_CONSOLE;
                }else if (strcmp("while", yytext) == 0) {
                    return token::KW_WHILE;
                }
                yylval->yyText = (char *) malloc(strlen(yytext));
                strcpy(yylval->yyText, yytext);

                return token::IDENTIFIER;

              }

[0-9]+        {
                  yylval->tIntegerValue = atoi(yytext);
                  return token::T_INTEGER;
              }

[0-9]+(\.[0-9][0-9]?) {
                  yylval->tDecimalValue = atof(yytext);
                  return token::T_DECIMAL;
              }

[0-9]+        {
                  yylval->tIntegerValue = atoi(yytext);
                  return token::T_INTEGER;
              }

"."           {return '.';}

"+"           {return '+';}
"-"           {return '-';}
"*"           {return '*';}
"/"           {return '/';}
"%"           {return '%';}
"="           {return '=';}
"<"           {return '<';}
">"           {return '>';}
"!"           {return '!';}
">="          { return token::TOK_GTE; }
"<="          { return token::TOK_LTE; }
"=="          { return token::TOK_EQUALITY; }
"!="          { return token::TOK_NEQUALITY; }

"{"           {return '{';}
"}"           {return '}';}

"("           {return '(';}
")"           {return ')';}

"["           {return '[';}
"]"           {return ']';}



";"           {return ';';}




[ \t]+       STEP();

[\n\r]+         {
                    STEP();
                    // LINE(yyleng); //return token::TOK_EOF;
                    // return '\n';
                }

.             {
                std::cerr << *driver.cursor << " Unexpected token : "
                                              << *yytext << std::endl;
                driver.error_ = (driver.error_ == 127 ? 127
                                : driver.error_ + 1);
                STEP ();
              }

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
