#include<AstNode.h>

AstNode::AstNode(){}
AstNode::AstNode(TOKEN aToken){
    token = aToken;
}
// AstNode::~AstNode(){
//     delete[] theParentNode;
// }
AstNode::AstNode(const AstNode& astNode){
    token = astNode.token;
    childNodes = astNode.childNodes;
    // AstNode parentNodeCopy;
    theParentNode = astNode.theParentNode;
}

void AstNode::setNextChild(AstNode newNode){
    childNodes.push_back(newNode);
}

void AstNode::setTheParenNode(AstNode& aParentNode){
    theParentNode = &aParentNode;
}