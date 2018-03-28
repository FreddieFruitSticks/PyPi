#include <Scanner.h>

#ifndef _PARSER_H
#define _PARSER_H
bool parseProgram(TOKEN*);
bool parseDeclarations(TOKEN*);
bool parseDeclaration(TOKEN*);
bool testDeclarationAndAdvance(TOKEN*);
#endif /*_PARSER_H*/