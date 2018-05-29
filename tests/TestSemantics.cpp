#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>
#include <SemanticAnalyser.h>

bool testSimpleTypeCheck(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest1"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    
    AbstractSyntaxTree* treePtr = &tree;
    typeChecking(treePtr);
    return false;
}

void test_semantics(){
    VERIFY("SourceTest1 - test simple type check", testSimpleTypeCheck());
}

// register suite
void semantics_suite(){
    TEST_SUITE("SEMANTIC SUITE", &test_semantics);
}