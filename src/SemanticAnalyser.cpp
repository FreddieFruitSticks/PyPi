#include<SemanticAnalyser.h>
#include<AstNode.h>
#include<Scanner.h>
#include<Parser.h>
#include<utility>

std::map<const std::string, std::string[2]> SemanticAnalyser::symbolTable;

SemanticAnalyser::~SemanticAnalyser(){
    symbolTable.clear();
}

void semanticAnalyseOperator(AstNode& node){
    if(checkOperator(node.childNodes.back()->token.type)){
        semanticAnalyseOperator(*node.childNodes.back());
        return;
    }
    if(node.childNodes.front()->token.type == INT_NUM){
        if(node.childNodes.back()->token.type != INT_NUM){
            throw std::runtime_error("type mismatch for operator");
        }
    }else if(node.childNodes.front()->token.type == FLOAT_NUM){
        if(node.childNodes.back()->token.type != FLOAT_NUM){
            throw std::runtime_error("type mismatch for operator");
        }
    }else{
        throw std::runtime_error("unsupported types of operator");
    }
}

void SemanticAnalyser::processor(AstNode node){
    if(node.theParentNode != NULL){
        // std::cout<<"!!!! "<< node.token << " parent:  "<< node.theParentNode->token <<std::endl;
    }
    if(node.token.type == FLOAT_DCL || node.token.type == INT_DCL){
        std::string declarationEntry[2];
        AstNode idNode;
        if (node.childNodes.front()->token.type == ID && 
            node.childNodes.front()->token.value != ""){
            
            idNode = *(node.childNodes.front());
            if(node.token.type == FLOAT_DCL){
                declarationEntry[0] = "float";
                declarationEntry[1] = "variable";
            }else{
                declarationEntry[0] = "int";     
                declarationEntry[1] = "variable";     
            }
            symbolTable.insert(std::pair<const std::string, std::string[2]>
                (idNode.token.value, declarationEntry));
        }else{
            throw std::runtime_error("Float declaration has no id");
        }
    }else if(node.token.type == ASSIGN){
        if(node.childNodes.front()->token.type == ID){
            AstNode idNode = *node.childNodes.front();
            std::string variable = idNode.token.value;
            std::map<const std::string, std::string[2]>::iterator it = symbolTable.find(variable);
            
            if(it != SemanticAnalyser::symbolTable.end()){
                // std::string declarationEntry[2] = std::get<1>(*it);
                // std::cout << node.childNodes.back()->token.type << std::endl;
                if(node.childNodes.back()->token.type == INT_NUM){
                    if(std::get<1>(*it)[1] != "variable" || std::get<1>(*it)[0] != "int"){
                        throw std::runtime_error("type mismatch");
                    }
                }else if(node.childNodes.back()->token.type == FLOAT_NUM){
                    if(std::get<1>(*it)[1] != "variable" || std::get<1>(*it)[0] != "float"){
                        throw std::runtime_error("type mismatch");
                    }
                }else if(checkOperator(node.childNodes.back()->token.type)){
                    AstNode plusNode = *node.childNodes.back();
                    if(plusNode.childNodes.front()->token.type == INT_NUM){
                        if(std::get<1>(*it)[1] != "variable" || std::get<1>(*it)[0] != "int"){
                            throw std::runtime_error("variable Assignment mismatch");
                        }
                    }else if(plusNode.childNodes.front()->token.type == FLOAT_NUM){
                        if(std::get<1>(*it)[1] != "variable" || std::get<1>(*it)[0] != "float"){
                            throw std::runtime_error("variable Assignment mismatch");
                        }
                    }else{
                        semanticAnalyseOperator(node);
                    }
                }else{
                    throw std::runtime_error("Cannot assign id to bad type");
                }
            }else {
                throw std::runtime_error("Variable not declared");
            }
        }
    }else if(checkOperator(node.token.type)){
        semanticAnalyseOperator(node);
    }
}

void SemanticAnalyser::typeChecking(AbstractSyntaxTree* AST){
    std::vector<AstNode>* stack = new std::vector<AstNode>();
    stack->push_back(AST->parentNode);
    AST->processSyntaxTree(stack, SemanticAnalyser::processor);
}