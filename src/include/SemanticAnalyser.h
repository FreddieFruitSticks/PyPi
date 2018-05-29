#ifndef SEMANTIC_ANALYSER_H
#define SEMANTIC_ANALYSER_H

#include<AbstractSyntaxTree.h>

void buildSyntaxTable();
void typeChecking(AbstractSyntaxTree*);

#endif