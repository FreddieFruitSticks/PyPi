#include <Parser.h>
#include <Scanner.h>

bool parseProgram(TOKEN* tokenPtr){
	std::cout << "!!!!!!!!!!!!!!!!" << *(tokenPtr) << std::endl;

	if (parseDeclarations(tokenPtr)){
		return true;
	}
	return false;
}

bool parseDeclarations(TOKEN* tokenPtr){
	if (parseDeclaration(tokenPtr)){
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
	TOKEN token;
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
	std::cout << "!!!!!!!!!!!!!!!!" << *(tokenPtr) << std::endl;

	return true;
}