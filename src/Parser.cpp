#include <Parser.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <AbstractSyntaxTree.h>

AstNode createNode(TokenType tokenType, std::string tokenValue){
	TOKEN token;
	token.type = tokenType;
	if(tokenValue != "") token.value = tokenValue;
	return AstNode(token);
}

AbstractSyntaxTree initialiseAST(TokenStream* tokenStream){
	TOKEN programToken;
	programToken.type = NIL;
	programToken.value = "PROGRAM";
	AstNode programNode(programToken);
	AbstractSyntaxTree* AST = new AbstractSyntaxTree(programNode);

	bool isParsed = parseProgram(tokenStream, AST);

	if(isParsed) return *AST;
	throw "Invalid parser Error";
}

bool parseProgram(TokenStream* tokenStream, AbstractSyntaxTree* AST){
	if(!atLeastOneNonTerminal(tokenStream, AST)) return false;
	if(tokenStream->peekCurrent().type == END_OF_FILE){
		AstNode endFileNode = createNode(END_OF_FILE, "");
		AST->parentNode.setNextChild(endFileNode);
		return true;
	}else{
		return parseProgram(tokenStream, AST);
	}
	return false;
}

bool atLeastOneNonTerminal(TokenStream* tokenStream, AbstractSyntaxTree* AST){
	if(tokenStream->peekCurrent().type == END_OF_FILE) return true; 
	AstNode* dclNode = parseDeclaration(tokenStream);
	if(dclNode == NULL){
		if(!parseAssignment(tokenStream)){
			if(!parsePrintStatement(tokenStream)){
				if(!parseOperatorStatement(tokenStream)){
					return false;
				}
			}
		}
	}else{
		AST->parentNode.setNextChild(*dclNode);
	}
	return true;
}

bool parseAssignment(TokenStream* tokenStream){
	if(!checkId(tokenStream->peekCurrent().type)) return false;
	
	if(checkAssign(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkNumber(tokenStream->peekNext().type) || checkId(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkOperator(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
		return parseOperatorExpression(tokenStream);
	}
	tokenStream->moveToNext();
	
	return true;
}

bool parseOperatorExpression(TokenStream* tokenStream){
	if(!checkOperator(tokenStream->peekCurrent().type)) return false;

	if(checkNumber(tokenStream->peekNext().type) || checkId(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkOperator(tokenStream->peekNext().type)){
		tokenStream->moveToNext();		 
		return parseOperatorExpression(tokenStream);
	}
	tokenStream->moveToNext();	
	return true;
}

AstNode* parseDeclaration(TokenStream* tokenStream){
	AstNode* typeNode = checkType(tokenStream->peekCurrent());
	if(typeNode == NULL) return NULL;
	AstNode* idNode = checkId(tokenStream->peekNext());
	if(idNode != NULL){
		typeNode->setNextChild(*idNode);
		tokenStream->moveToNext();
	}else {
		return NULL;
	}
	tokenStream->moveToNext();	
	return typeNode;
}

bool parsePrintStatement(TokenStream* tokenStream){
	if(!checkPrint(tokenStream->peekCurrent().type)) return false;

	if(checkId(tokenStream->peekNext().type) || checkNumber(tokenStream->peekNext().type)) {
		tokenStream->moveToNext();
	}else{
		return false;
	}
	tokenStream->moveToNext();
	return true;
}

bool parseOperatorStatement(TokenStream* tokenStream){
	if(!checkId(tokenStream->peekCurrent().type) && !checkNumber(tokenStream->peekCurrent().type)) return false;
	if(checkOperator(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkId(tokenStream->peekNext().type) || checkNumber(tokenStream->peekNext().type)){
		tokenStream->moveToNext();
	}else {
		return false;
	}
	tokenStream->moveToNext();
	return true;
}

bool checkOperator(TokenType tokenType){
	if(tokenType != PLUS && tokenType != MINUS) return false;
	return true;
}

bool checkPrint(TokenType tokenType){
	if(tokenType != PRINT) return false;
	return true;	
}

bool checkAssign(TokenType tokenType){
	if(tokenType != ASSIGN) return false;
	return true;	
}

bool checkNumber(TokenType tokenType){
	if(tokenType != INT_NUM && tokenType != FLOAT_NUM) return false;
	return true;
}

AstNode* checkType(TOKEN token){
	if(token.type == FLOAT_DCL || token.type == INT_DCL) {
		return new AstNode(token);
	}
	return NULL;
}
bool checkId(TokenType tokenType){
	if(tokenType != ID) return false;
	return true;
	
}
AstNode* checkId(TOKEN token){
	if(token.type != ID) return NULL;
	return new AstNode(token);
}
