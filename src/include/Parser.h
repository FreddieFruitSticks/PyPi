#ifndef _PARSER_H
#define _PARSER_H

#include <Scanner.h>
#include <TokenStream.h>

bool parseProgram(TokenStream*);
bool parseDeclaration(TokenStream*);
bool checkType(TokenType);
bool checkId(TokenType);
bool parseAssignment(TokenStream*);
bool checkAssign(TokenType);
bool checkNumber(TokenType);
bool atLeastOneNonTerminal(TokenStream*);
bool parsePrintStatement(TokenStream*);
bool checkPrint(TokenType);
bool parseOperatorStatement(TokenStream*);
bool checkOperator(TokenType);
#endif /*_PARSER_H*/