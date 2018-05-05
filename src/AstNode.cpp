#include<AstNode.h>

AstNode::AstNode(TOKEN aToken){
    token = aToken;
}

AstNode::AstNode(){}

void AstNode::setNextChild(AstNode newNode){
    childNodes.push_back(newNode);
}