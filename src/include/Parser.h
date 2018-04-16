#ifndef _PARSER_H
#define _PARSER_H

#include <Scanner.h>
#include <TokenStream.h>

bool parseProgram(TokenStream*);
bool parseDeclarations(TokenStream*);
bool parseType(TokenStream*);
bool parseId(TokenStream*);
#endif /*_PARSER_H*/