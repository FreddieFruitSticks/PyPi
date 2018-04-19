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
	if(!parseDeclaration(tokenStream)){
		if(!parseAssignment(tokenStream)){
			if(!parsePrintStatement(tokenStream)){
				return false;
			}
		}
	}
	return true;
}

bool parseAssignment(TokenStream* tokenStream){
	if(!parseId(tokenStream)) return false;
	if(!parseAssign(tokenStream)) return false;
	if(!parseNumber(tokenStream)) return false;
	return true;
}

bool parseDeclaration(TokenStream* tokenStream){
	if(!parseType(tokenStream)) return false;
	if(!parseId(tokenStream)) return false;
	return true;
}

bool parsePrintStatement(TokenStream* tokenStream){
	if(!parsePrint(tokenStream)) return false;
	if(!parseId(tokenStream) && !parseNumber(tokenStream)) return false;
	return true;
}

bool parsePrint(TokenStream* tokenStream){
	if(tokenStream->peekCurrent().type != PRINT) return false;
	tokenStream->moveToNext();
	return true;	
}

bool parseAssign(TokenStream* tokenStream){
	if(tokenStream->peekCurrent().type != ASSIGN) return false;
	tokenStream->moveToNext();
	return true;	
}

bool parseNumber(TokenStream* tokenStream){
	if(tokenStream->peekCurrent().type != INT_NUM && tokenStream->peekCurrent().type != FLOAT_NUM) return false;
	tokenStream->moveToNext();
	return true;
}

bool parseType(TokenStream* tokenStream){
	if(tokenStream->peekCurrent().type != FLOAT_DCL && tokenStream->peekCurrent().type != INT_DCL) return false;
	tokenStream->moveToNext();
	return true;
}
bool parseId(TokenStream* tokenStream){
	if(tokenStream->peekCurrent().type != ID) return false;
	tokenStream->moveToNext();
	return true;
}
