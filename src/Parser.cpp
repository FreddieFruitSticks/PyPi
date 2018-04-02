#include <Parser.h>
#include <Scanner.h>

bool parseProgram(TOKEN* tokenPtr){

	if (parseDeclarations(tokenPtr)){
		return true;
	}
	return false;
}

bool parseDeclarations(TOKEN* tokenPtr){
	while (parseDeclaration(tokenPtr)){
		return true;
	}
	return false;
}

bool parseDeclaration(TOKEN* tokenPtr){
	if(testDeclarationAndAdvance(tokenPtr)){
		return true;
	}
}

bool testDeclarationAndAdvance(TOKEN* tokenPtr){
	if ((*tokenPtr).type == "floatDcl" || (*tokenPtr).type == "intDcl"){
		tokenPtr++;
	}else {
		return false;
	}

	if ((*tokenPtr).type == "id"){
		tokenPtr++;
	}else {
		return false;
	}

	return true;
}