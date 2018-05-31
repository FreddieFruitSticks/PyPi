#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>
#include <SemanticAnalyser.h>
#include <utility>
#include <map>

bool testSimpleTypeCheck(){
    // Scanner
    try{
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest1"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser;
        semanticAnalyser.typeChecking(treePtr);
        std::map<const std::string, std::string[2]>::iterator itA;
        std::map<const std::string, std::string[2]>::iterator itB;
        itA = SemanticAnalyser::symbolTable.find("numA");
        itB = SemanticAnalyser::symbolTable.find("numB");

        if(itA != SemanticAnalyser::symbolTable.end() &&
            itB != SemanticAnalyser::symbolTable.end()){
            if(std::get<1>(*itA)[0] == "float" && 
                std::get<1>(*itB)[0] == "int"){
                return true;
            }
        }
    }catch(std::runtime_error e){
        std::cerr <<  e.what() << std::endl;
    }
    return false;
}

void test_semantics(){
    VERIFY("SourceTest1 - test simple type check", testSimpleTypeCheck());
}

// register suite
void semantics_suite(){
    TEST_SUITE("SEMANTIC SUITE", &test_semantics);
}