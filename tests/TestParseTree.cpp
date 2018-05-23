#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>

bool testForDclNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest1"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN dclToken;
    TOKEN idToken;
    eofToken.type = END_OF_FILE;
    dclToken.type = INT_DCL;
    idToken.type = ID;
    idToken.value = "num";
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == dclToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == idToken) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool testForPrintNodes(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest2"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN intNumToken;
    TOKEN idToken;
    TOKEN printToken;

    printToken.type = PRINT;
    eofToken.type = END_OF_FILE;
    intNumToken.type = INT_NUM;
    intNumToken.value = "5";
    idToken.type = ID;
    idToken.value = "numA";
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == printToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == idToken) {
                    tree.parentNode.childNodes.pop_back();
                    if(tree.parentNode.childNodes.back().token == printToken){
                        if(tree.parentNode.childNodes.back().childNodes.back().token == intNumToken){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


bool testForOperatorNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest3"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN numberToken1;
    TOKEN numberToken2;
    TOKEN operatorToken;
    
    eofToken.type = END_OF_FILE;
    numberToken1.type = INT_NUM;
    numberToken1.value = "6";
    numberToken2.type = INT_NUM;
    numberToken2.value = "5";
    operatorToken.type = PLUS;
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == operatorToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == numberToken1) {
                    tree.parentNode.childNodes.back().childNodes.pop_back();
                    if(tree.parentNode.childNodes.back().childNodes.back().token == numberToken2) {
                        return true;
                    }
                    
                }
            }
        }
    }
    return false;
}

bool testForMultipleOperatorNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest4"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN numberToken1;
    TOKEN numberToken2;
    TOKEN numberToken3;
    TOKEN printNumberToken;
    TOKEN operatorToken;
    TOKEN printToken;

    printToken.type = PRINT;
    eofToken.type = END_OF_FILE;
    numberToken1.type = INT_NUM;
    numberToken1.value = "1";
    numberToken2.type = INT_NUM;
    numberToken2.value = "2";
    numberToken3.type = INT_NUM;
    numberToken3.value = "3";
    operatorToken.type = PLUS;
    printNumberToken.type = INT_NUM;
    printNumberToken.value = "5";
    programToken.type = NIL;
    programToken.value = "PROGRAM";

    if(tree.parentNode.token == programToken) {
        if(tree.parentNode.childNodes.back().token == eofToken) {
            tree.parentNode.childNodes.pop_back();
            if(tree.parentNode.childNodes.back().token == printToken){
                if(tree.parentNode.childNodes.back().childNodes.back().token == printNumberToken){
                    tree.parentNode.childNodes.pop_back();
                    if(tree.parentNode.childNodes.back().token == operatorToken){
                        if(tree.parentNode.childNodes.back().childNodes.back().token == operatorToken) {
                            if(tree.parentNode.childNodes.back().childNodes.back().childNodes.back().token == numberToken3){
                                tree.parentNode.childNodes.back().childNodes.back().childNodes.pop_back();
                                if(tree.parentNode.childNodes.back().childNodes.back().childNodes.back().token == numberToken2){
                                    tree.parentNode.childNodes.back().childNodes.pop_back();
                                    if(tree.parentNode.childNodes.back().childNodes.back().token == numberToken1) {
                                        return true;
                                    }
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
    return false;
}

void printNodes(AstNode node, std::vector<AstNode>* allNodes){
    if(node.theParentNode != NULL){
        std::cout<<"*(*(*(*( "<<node.token<<" "<<node.theParentNode->token<<std::endl;
    }
    allNodes->push_back(node);
}

bool testAssignNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest5"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN idToken;
    TOKEN assignToken;
    TOKEN numberToken;

    programToken.type = NIL;
    programToken.value = "PROGRAM";
    eofToken.type = END_OF_FILE;
    idToken.type = ID;
    idToken.value = "numA";
    assignToken.type = ASSIGN;
    numberToken.type = INT_NUM;
    numberToken.value = "5";

    std::vector<AstNode>* stack = new std::vector<AstNode>();
    std::vector<AstNode>* allNodes = new std::vector<AstNode>();
    stack->push_back(tree.parentNode);
    void (*processor)(AstNode, std::vector<AstNode>*) = &printNodes;
    tree.processSyntaxTree(stack, processor, allNodes);

    TOKEN tokensArray[5] = {programToken, eofToken, assignToken, numberToken, idToken};
    int i = 0;
    for(std::vector<AstNode>::iterator it = allNodes->begin(); it != allNodes->end(); it++){
        // std::cout << it->token << std::endl;
        // std::cout << it->token << std::endl;
        if(it->token != tokensArray[i]){
            std::cout << "!!!!!!!" << std::endl;
            return false;
        }

        i++;
    }
    return true;
}

bool testAssignOfSumNode(){
    std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/parse_tree/sourceTest6"));
    TokenStream* tokenStream = new TokenStream(tokens);

    AbstractSyntaxTree tree = initialiseAST(tokenStream);
    TOKEN programToken;
    TOKEN eofToken;
    TOKEN idToken;
    TOKEN assignToken;
    TOKEN numberToken1;
    TOKEN numberToken2;
    TOKEN plusToken;

    programToken.type = NIL;
    programToken.value = "PROGRAM";
    eofToken.type = END_OF_FILE;
    idToken.type = ID;
    idToken.value = "numA";
    assignToken.type = ASSIGN;
    numberToken1.type = INT_NUM;
    numberToken1.value = "1";
    numberToken2.type = INT_NUM;
    numberToken2.value = "2";
    plusToken.type = PLUS;

    AstNode programNode(programToken);
    AstNode eofNode(eofToken);
    eofNode.setTheParenNode(programNode);
    AstNode assignNode(assignToken);
    assignNode.setTheParenNode(programNode);
    AstNode plusNode(plusToken);
    plusNode.setTheParenNode(assignNode);    
    AstNode numberNode2(numberToken2);
    numberNode2.setTheParenNode(plusNode);
    AstNode numberNode1(numberToken1);
    numberNode1.setTheParenNode(plusNode);
    AstNode idNode(idToken);
    idNode.setTheParenNode(programNode);

    std::vector<AstNode>* stack = new std::vector<AstNode>();
    std::vector<AstNode>* allNodes = new std::vector<AstNode>();
    stack->push_back(tree.parentNode);
    void (*processor)(AstNode, std::vector<AstNode>*) = &printNodes;
    tree.processSyntaxTree(stack, processor, allNodes);

    TOKEN tokensArray[7] = {programToken, eofToken, assignToken, plusToken, numberToken2, numberToken1, idToken};
    AstNode astNodeArray[7] = {programNode, eofNode, assignNode, plusNode, numberNode2, numberNode1, idNode};
    int i = 0;
    for(std::vector<AstNode>::iterator it = allNodes->begin(); it != allNodes->end(); it++){
        // std::cout << it->token << std::endl;
            // std::cout <<"!!!"<< (it->theParentNode)->token<<std::endl;
        if(it->token != astNodeArray[i].token || 
            ((it->token).value != "PROGRAM" && it->theParentNode == NULL) ||
            ((it->token).value != "PROGRAM" && (it->theParentNode)->token != (astNodeArray[i].theParentNode)->token)){
            std::cout<<it->token<<std::endl;
            if(it->theParentNode == NULL){
                std::cout<<"Parent is NULL"<<std::endl;
                
            }
            return false;
        }
        i++;
    }

    return true;

    // if(tree.parentNode.token == programToken) {
    //     if(tree.parentNode.childNodes.back().token == eofToken) {
    //         tree.parentNode.childNodes.pop_back();
    //         if(tree.parentNode.childNodes.back().token == assignToken){
    //             if(tree.parentNode.childNodes.back().childNodes.back().token == numberToken1) {
    //                 tree.parentNode.childNodes.back().childNodes.pop_back();
    //                 if(tree.parentNode.childNodes.back().childNodes.back().token == idToken){
    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    // }
    // return false;
}

void test_parse_AST(){
    VERIFY("SourceTest1 - Tree has declaration Node-> id node", testForDclNode());
    VERIFY("SourceTest2 - print->id and print->num nodes", testForPrintNodes());
    VERIFY("SourceTest3 - operator nodes", testForOperatorNode());
    VERIFY("SourceTest4 - multiple operator nodes", testForMultipleOperatorNode());
    VERIFY("SourceTest5 - assign nodes", testAssignNode());
    VERIFY("SourceTest6 - assign sum nodes", testAssignOfSumNode());
}

// register suite
void parse_tree_suite(){
    TEST_SUITE("PARSE AST SUITE", &test_parse_AST);
}