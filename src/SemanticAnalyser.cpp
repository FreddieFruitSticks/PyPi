#include<SemanticAnalyser.h>
#include<AstNode.h>
#include<Scanner.h>

std::map<const std::string, std::string[2]> SemanticAnalyser::symbolTable;

void SemanticAnalyser::processor(AstNode node){
    if(node.theParentNode != NULL){
        std::cout<<"!!!! "<< node.token << " parent:  "<< node.theParentNode->token <<std::endl;
    }
    if(node.token.type == FLOAT_DCL || node.token.type == INT_DCL){
        std::string declarationEntry[2];
        AstNode idNode;
        if (node.childNodes.front()->token.type == ID && 
            node.childNodes.front()->token.value != ""){
            
            idNode = *(node.childNodes.front());
            if(node.token.type == FLOAT_DCL){
                declarationEntry[0] = "float";
            }else{
                declarationEntry[0] = "int";                
            }
            symbolTable.insert(std::pair<const std::string, std::string[2]>
                (idNode.token.value, declarationEntry));
        }else{
            throw std::runtime_error("Float declaration has no id");
        }
    }
}

void SemanticAnalyser::typeChecking(AbstractSyntaxTree* AST){
    std::vector<AstNode>* stack = new std::vector<AstNode>();
    stack->push_back(AST->parentNode);
    AST->processSyntaxTree(stack, SemanticAnalyser::processor);
}