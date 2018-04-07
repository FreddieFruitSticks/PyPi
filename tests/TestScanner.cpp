#include <Scanner.h>
#include <string>
#include <Testpp.h>

bool checkTokenSequenceOf1(TOKEN* tokenPtr){
    if(tokenPtr->type != FLOAT_DCL) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != INT_DCL) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != PLUS) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != END_OF_FILE) return false;    
    return true;
}

void test_scanner(){
    TOKEN* tokenPtr;
	tokenPtr = scan(std::string("./tests/test_sources/sourceTest1"));
	VERIFY("Verify correct Token Sequence of sourceTest1", checkTokenSequenceOf1(tokenPtr));
}

void scanner_suite(){
    TEST_SUITE("SCANNER SUITE", &test_scanner);
}