#include <Parser.h>
#include <Scanner.h>
#include <TokenStream.h>

bool parseProgram(TokenStream* tokenStream){

	if(parseDeclarations(tokenStream)){
		return true;
	}
	return false;
}

bool parseDeclarations(TokenStream* tokenStream){
	if(!parseType(tokenStream)) return false;
	if(!parseId(tokenStream)) return false;
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
