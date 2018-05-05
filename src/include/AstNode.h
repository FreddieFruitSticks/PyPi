#ifndef _ASTNODE_H
#define _ASTNODE_H
#include <Scanner.h>

class AstNode{
    public:
        TOKEN token;
        std::vector<AstNode> childNodes;
    
    AstNode(TOKEN);
    AstNode();
    void setNextChild(AstNode);
};
#endif