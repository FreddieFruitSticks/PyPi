#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>

bool testForProgramNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest1"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    eofToken.type = END_OF_FILE;
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.front().token == eofToken) {
            return true;
        }
    }

    return false;
}

void test_parse_AST(){
    VERIFY("Tree contains program node", testForProgramNode());
}

// register suite
void parse_tree_suite(){
    TEST_SUITE("PARSE AST SUITE", &test_parse_AST);
}