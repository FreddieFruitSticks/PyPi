#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H

#include <AstNode.h>

class AbstractSyntaxTree{
    private:
        AstNode parentNode;
    public:
        AbstractSyntaxTree(AstNode);
        AstNode breadthFirstSearch(std::vector<AstNode>, TOKEN);
};

#endif