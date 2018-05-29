#include <AbstractSyntaxTree.h>
#include <AstNode.h>
#include <Scanner.h>

AbstractSyntaxTree::AbstractSyntaxTree(AstNode aParentNode){
    parentNode = aParentNode;
}

AbstractSyntaxTree::AbstractSyntaxTree(){
    TOKEN programToken;
	programToken.type = NIL;
	programToken.value = "PROGRAM";
	AstNode programNode(programToken);
    parentNode = programNode;
};

AstNode AbstractSyntaxTree::breadthFirstSearch(std::vector<AstNode> vector, TOKEN token){
    AstNode node = vector.front();
    
    if(node.token == token) return node;
    vector.erase(vector.begin(), vector.begin() + 1);
    if(!node.childNodes.empty()){
        for(std::vector<AstNode*>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); it++){
            vector.push_back(**it);
        }
    }

    return breadthFirstSearch(vector, token);
}

void AbstractSyntaxTree::processSyntaxTree(std::vector<AstNode>* stack, void (*processor)(AstNode node, std::vector<AstNode>* allNode), std::vector<AstNode>* allNodes){
    
    if(!stack->empty()){
        AstNode node = stack->front();
        stack->erase(stack->begin(), stack->begin() + 1);
        
        (*processor)(node, allNodes);
        if(!node.childNodes.empty()){
            for(std::vector<AstNode*>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); it++){
                stack->push_back(**it);
            }
        }
        processSyntaxTree(stack, processor, allNodes);
    }
}

void AbstractSyntaxTree::processSyntaxTree(std::vector<AstNode>* stack, void (*processor)(AstNode node)){
    
    if(!stack->empty()){
        AstNode node = stack->front();
        stack->erase(stack->begin(), stack->begin() + 1);
        if(node.theParentNode != NULL){
            std::cout<<"!!!! "<< node.token << " parent:  "<< node.theParentNode->token <<std::endl;
        }
        // node.accept(processor);
        if(!node.childNodes.empty()){
            for(std::vector<AstNode*>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); it++){
                stack->push_back(**it);
            }
        }
        processSyntaxTree(stack, processor);
    }
}