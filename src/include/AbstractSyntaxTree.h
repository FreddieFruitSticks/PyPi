#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H

#include <AstNode.h>

class AbstractSyntaxTree{
    public:
        AstNode parentNode;
    public:
        AbstractSyntaxTree(AstNode);
        AbstractSyntaxTree();
    
        AstNode breadthFirstSearch(std::vector<AstNode>, TOKEN);
};

#endif