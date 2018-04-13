#include <Parser.h>
#include <Scanner.h>

bool parseProgram(TOKEN* tokenPtr){
	if(tokenPtr->type == FLOAT_DCL || tokenPtr->type == INT_DCL){
		tokenPtr++;
		if(tokenPtr->type == ID){
			return true;
		}
	}
	return false;
}