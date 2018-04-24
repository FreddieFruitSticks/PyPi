#include <Parser.h>
#include <Scanner.h>
#include <TokenStream.h>

bool parseProgram(TokenStream* tokenStream){
	if(!atLeastOneNonTerminal(tokenStream)) return false;
	if(tokenStream->peekCurrent().type == END_OF_FILE){
		return true;
	}else{
		return parseProgram(tokenStream);
	}
	return false;
}

bool atLeastOneNonTerminal(TokenStream* tokenStream){
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
