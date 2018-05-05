#include <AbstractSyntaxTree.h>
#include <AstNode.h>
#include <Scanner.h>

AbstractSyntaxTree::AbstractSyntaxTree(AstNode aParentNode){
    parentNode = aParentNode;
}

AstNode AbstractSyntaxTree::breadthFirstSearch(std::vector<AstNode> vector,TOKEN token){
    AstNode node = vector.front();

    if(node.token == token) return node;
    vector.erase(vector.begin(), vector.begin() + 1);
    if(!node.childNodes.empty()){
        for(std::vector<AstNode>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); it++){
            vector.push_back(*it);
        }
    }

    return breadthFirstSearch(vector, token);
}