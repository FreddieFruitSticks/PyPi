#include <Parser.h>
#include <Scanner.h>
#include <string>
#include <Testpp.h>
#include <TestScanner.h>

bool checkParser1(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parser/sourceTest1"));
	TokenStream* tokenStream = new TokenStream(tokens);
    return parseProgram(tokenStream);
}

bool checkParser2(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parser/sourceTest2"));
	TokenStream* tokenStream = new TokenStream(tokens);
    return parseProgram(tokenStream);
}

bool checkParser3(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parser/sourceTest3"));
	TokenStream* tokenStream = new TokenStream(tokens);
    return parseProgram(tokenStream);
}

bool checkParser4(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parser/sourceTest4"));
	TokenStream* tokenStream = new TokenStream(tokens);
    return parseProgram(tokenStream);
}

bool checkParser5(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parser/sourceTest5"));
	TokenStream* tokenStream = new TokenStream(tokens);
    return parseProgram(tokenStream);
}

void test_parser(){
    VERIFY("sourceTest1 passes as a legitimate program", checkParser1());
    VERIFY("sourceTest2 passes as a legitimate program", checkParser2());
    VERIFY("sourceTest3 passes as a legitimate program", checkParser3());
    VERIFY("sourceTest4 passes as a legitimate program", checkParser4());
    VERIFY("sourceTest5 passes as a legitimate program", checkParser5());
}

// register suite
void parser_suite(){
    TEST_SUITE("PARSER SUITE", &test_parser);
}