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
AstNode* checkNumber(TOKEN);
bool checkNumber(TokenType);
AstNode* checkNumber(TOKEN);
bool atLeastOneNonTerminal(TokenStream*, AbstractSyntaxTree*);
AstNode* parsePrintStatement(TokenStream*);
AstNode* checkPrint(TOKEN);
AstNode* parseOperatorStatement(TokenStream*);
bool checkOperator(TokenType);
AstNode* checkOperator(TOKEN);
bool parseOperatorExpression(TokenStream*);
#endif /*_PARSER_H*/