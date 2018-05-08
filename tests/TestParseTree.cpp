#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>

bool testForDclNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest1"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN dclToken;
    TOKEN idToken;
    eofToken.type = END_OF_FILE;
    dclToken.type = INT_DCL;
    idToken.type = ID;
    idToken.value = "num";
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == dclToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == idToken) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool testForPrintNodes(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest2"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN intNumToken;
    TOKEN idToken;
    TOKEN printToken;

    printToken.type = PRINT;
    eofToken.type = END_OF_FILE;
    intNumToken.type = INT_NUM;
    intNumToken.value = "5";
    idToken.type = ID;
    idToken.value = "numA";
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == printToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == idToken) {
                    tree.parentNode.childNodes.pop_back();
                    if(tree.parentNode.childNodes.back().token == printToken){
                        if(tree.parentNode.childNodes.back().childNodes.back().token == intNumToken){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;

    return false;
}

void test_parse_AST(){
    VERIFY("SourceTest1 - Tree has declaration Node-> id node", testForDclNode());
    VERIFY("SourceTest2 - print->id and print->num nodes", testForPrintNodes());
}

// register suite
void parse_tree_suite(){
    TEST_SUITE("PARSE AST SUITE", &test_parse_AST);
}