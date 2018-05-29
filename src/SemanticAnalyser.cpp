#include<SemanticAnalyser.h>
#include<AstNode.h>
#include<Scanner.h>

void processor(AstNode node){

    std::cout << node.token << std::endl;

}

void typeChecking(AbstractSyntaxTree* AST){
    std::vector<AstNode>* stack = new std::vector<AstNode>();
    stack->push_back(AST->parentNode);
    AST->processSyntaxTree(stack, processor);
}