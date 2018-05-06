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
	if(!parseDeclaration(tokenStream)){
		if(!parseAssignment(tokenStream)){
			if(!parsePrintStatement(tokenStream)){
				if(!parseOperatorStatement(tokenStream)){
					return false;
				}
			}
		}
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

bool parseDeclaration(TokenStream* tokenStream){
	if(!checkType(tokenStream->peekCurrent().type)) return false;
	if(checkId(tokenStream->peekNext().type)){
		tokenStream->moveToNext();
	}else {
		return false;
	}
	tokenStream->moveToNext();	
	return true;
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

bool checkType(TokenType tokenType){
	if(tokenType != FLOAT_DCL && tokenType != INT_DCL) return false;
	return true;
}
bool checkId(TokenType tokenType){
	if(tokenType != ID) return false;
	return true;
}
