#ifndef _PARSER_H
#define _PARSER_H

#include <Scanner.h>
#include <TokenStream.h>

bool parseProgram(TokenStream*);
bool parseDeclaration(TokenStream*);
bool parseType(TokenStream*);
bool parseId(TokenStream*);
bool parseAssignment(TokenStream*);
bool parseAssign(TokenStream*);
bool parseNumber(TokenStream*);
bool atLeastOneNonTerminal(TokenStream*);
bool parsePrintStatement(TokenStream*);
bool parsePrint(TokenStream*);
#endif /*_PARSER_H*/