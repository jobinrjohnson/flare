
#ifndef SCANPIT_HH_
#define SCANPIT_HH_

#include "parser.hh"

#ifndef YY_DECL
#define YY_DECL                                                                \
  int lang::Scanner::yylex(                               \
      lang::Parser::semantic_type *yylval, lang::Parser::location_type *,      \
      lang::Driver &driver)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer LangFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

namespace lang {
class Scanner : public LangFlexLexer {
public:
  Scanner();
  virtual ~Scanner();
  void setDebug(bool b);

//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Woverloaded-virtual"
  virtual int yylex(Parser::semantic_type *yylval,
                                   Parser::location_type *l, Driver &driver);
//#pragma clang diagnostic pop

};
} // namespace lang

#endif // SCANPIT_HH_
