#include <Testpp.h>
#include <Scanner.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>

bool testBFS(){
    TOKEN token;
    TOKEN token2;
    TOKEN token3;

    token.type = PLUS;
    token2.type = INT_NUM;
    token2.value = "5";
    token3.type = INT_NUM;
    token3.value = "6";

    AstNode node(token);
    AstNode node2(token2);
    AstNode node3(token3);

    node.setNextChild(node2);
    node.setNextChild(node3);

    AbstractSyntaxTree tree(node);

    std::vector<AstNode> vector;
    vector.push_back(node);
    AstNode node1 = tree.breadthFirstSearch(vector, token3);

    if(node1.token == token3){
        return true;
    }
    return false;
    
}

void test_AST(){
    VERIFY("BFS finds node", testBFS());
}

// register suite
void AST_suite(){
    TEST_SUITE("ABSTRACT SYNTAX SUITE", &test_AST);
}