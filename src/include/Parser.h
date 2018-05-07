#ifndef _PARSER_H
#define _PARSER_H

#include <Scanner.h>
#include <TokenStream.h>
#include <AbstractSyntaxTree.h>

bool parseProgram(TokenStream*, AbstractSyntaxTree*);
AbstractSyntaxTree initialiseAST(TokenStream*);
// bool parseDeclaration(TokenStream*);
AstNode* parseDeclaration(TokenStream*);
AstNode* checkType(TOKEN);
AstNode* checkId(TOKEN);
bool checkId(TokenType tokenType);
bool parseAssignment(TokenStream*);
bool checkAssign(TokenType);
bool checkNumber(TokenType);
bool atLeastOneNonTerminal(TokenStream*, AbstractSyntaxTree*);
bool parsePrintStatement(TokenStream*);
bool checkPrint(TokenType);
bool parseOperatorStatement(TokenStream*);
bool checkOperator(TokenType);
bool parseOperatorExpression(TokenStream*);
#endif /*_PARSER_H*/