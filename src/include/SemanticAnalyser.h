#ifndef SEMANTIC_ANALYSER_H
#define SEMANTIC_ANALYSER_H

#include<AbstractSyntaxTree.h>
#include<map>
class SemanticAnalyser{

    public:
        static std::map<const std::string, std::string[2]> symbolTable;
        static void processor(AstNode node);
        void buildSyntaxTable();
        void typeChecking(AbstractSyntaxTree*);
};

#endif