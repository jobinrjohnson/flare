//
// Created by jobinrjohnson on 26/05/21.
//

#ifndef FLARE_SCANNER_HELPER_H
#define FLARE_SCANNER_HELPER_H


#include <scanner.h>
#include <parser.hh>

#define STEP()                                                                 \
  do {                                                                         \
    driver.stepCursor();                                                     \
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

#define IS_TOKEN(a) \
    strcmp(a,yytext) == 0

int filterKwOrId(
        lang::Parser::semantic_type *yylval,
        const char *yytext,
        lang::Driver &driver
) {

    if (IS_TOKEN("let")) {
        return token::KW_LET;
    } else if (IS_TOKEN("if")) {
        return token::KW_IF;
    } else if (IS_TOKEN("else")) {
        return token::KW_ELSE;
    } else if (IS_TOKEN("log")) {
        return token::KW_LOG;
    } else if (IS_TOKEN("return")) {
        return token::KW_RETURN;
    } else if (IS_TOKEN("function")) {
        return token::KW_FUNCTION;
    } else if (IS_TOKEN("console")) {
        return token::KW_CONSOLE;
    } else if (IS_TOKEN("while")) {
        return token::KW_WHILE;
    } else if (IS_TOKEN("int")) {
        return token::KW_INT;
    } else if (IS_TOKEN("int32")) {
        return token::KW_INT32;
    } else if (IS_TOKEN("number")) {
        return token::KW_NUMBER;
    } else if (IS_TOKEN("int64")) {
        return token::KW_INT64;
    } else if (IS_TOKEN("bigint")) {
        return token::KW_BIGINT;
    } else if (IS_TOKEN("double")) {
        return token::KW_DOUBLE;
    } else if (IS_TOKEN("float")) {
        return token::KW_FLOAT;
    } else if (IS_TOKEN("class")) {
        return token::KW_CLASS;
    } else if (IS_TOKEN("new")) {
        return token::KW_NEW;
    } else if (IS_TOKEN("boolean")) {
        return token::KW_BOOLEAN;
    } else if (IS_TOKEN("void")) {
        return token::KW_VOID;
    } else if (IS_TOKEN("this")) {
        return token::KW_THIS;
    } else if (IS_TOKEN("true")) {
        yylval->tBoolValue = true;
        return token::T_BOOLEAN;
    } else if (IS_TOKEN("false")) {
        yylval->tBoolValue = false;
        return token::T_BOOLEAN;
    }
    yylval->yyText = (char *) malloc(strlen(yytext));
    strcpy(yylval->yyText, yytext);

    return token::IDENTIFIER;

}

int processString(
        lang::Parser::semantic_type *yylval,
        const char *yytext,
        lang::Driver &driver
) {

    int len = strlen(yytext);
    yylval->tStringValue = (char *) malloc(len - 2);

    // TODO handle escape sequences

    memcpy(yylval->tStringValue, &yytext[1], len - 2);
    yylval->tStringValue[len - 1] = '\0';

    return token::T_STRING;

}


void processUnexpected(
        lang::Parser::semantic_type *yylval,
        const char *yytext,
        lang::Driver &driver
) {
    std::cerr << *(driver.getCursor()) << " Unexpected token : "
              << *yytext << std::endl;

    int err = driver.getError() == 127 ? 127
                                       : driver.getError() + 1;
    driver.setError(err);
    STEP ();
}

#endif //FLARE_SCANNER_HELPER_H
