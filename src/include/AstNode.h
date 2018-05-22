#ifndef _ASTNODE_H
#define _ASTNODE_H
#include <Scanner.h>

class AstNode{
    public:
        TOKEN token;
        std::vector<AstNode> childNodes;
        AstNode* theParentNode = NULL;
    
    // AstNode(TOKEN, AstNode&);
    // AstNode(AstNode&);
    // AstNode(const AstNode& astNode);
    // ~AstNode();
    AstNode(TOKEN);
    AstNode();
    void setNextChild(AstNode);
    void setTheParenNode(AstNode&);
};
#endif