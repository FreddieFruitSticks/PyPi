#include <Scanner.h>
#include <string>
#include <Testpp.h>

bool checkTokenSequenceOf1(){
    TOKEN* tokenPtr;
	tokenPtr = scan(std::string("./tests/test_sources/sourceTest1"));

    if(tokenPtr->type != FLOAT_DCL) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != ASSIGN) return false;
    tokenPtr++;
    if(tokenPtr->type != FLOAT_NUM) return false;
    tokenPtr++;
    if(tokenPtr->type != INT_DCL) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != ASSIGN) return false;
    tokenPtr++;
    if(tokenPtr->type != INT_NUM) return false;
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

bool checkTokenSequenceOf2(){
    TOKEN* tokenPtr;
	tokenPtr = scan(std::string("./tests/test_sources/sourceTest2"));

    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != PLUS) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != END_OF_FILE) return false;    
    return true;
}

bool checkTokenSequenceOf3(){
    TOKEN* tokenPtr;
	tokenPtr = scan(std::string("./tests/test_sources/sourceTest3"));

    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != PLUS) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;    
    if(tokenPtr->type != MINUS) return false;
    tokenPtr++;    
    if(tokenPtr->type != ID) return false;
    tokenPtr++;    
    if(tokenPtr->type != FLOAT_DCL) return false;
    tokenPtr++;    
    if(tokenPtr->type != ID) return false;
    tokenPtr++;    
    if(tokenPtr->type != ASSIGN) return false;
    tokenPtr++;
    if(tokenPtr->type != ID) return false;
    tokenPtr++;
    if(tokenPtr->type != END_OF_FILE) return false;    
    return true;
}

void test_scanner(){
	VERIFY("Verify correct Token Sequence", checkTokenSequenceOf1());
	VERIFY("Verify spaces are ignored", checkTokenSequenceOf2());
	VERIFY("Verify operators are spaces invariant", checkTokenSequenceOf3());
}

// register suite
void scanner_suite(){
    TEST_SUITE("SCANNER SUITE", &test_scanner);
}