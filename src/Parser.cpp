#include <Parser.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <AbstractSyntaxTree.h>

AstNode createNode(TokenType tokenType, std::string tokenValue){
	TOKEN token;
	token.type = tokenType;
	if(tokenValue != "") token.value = tokenValue;
	return AstNode(token);
}

AbstractSyntaxTree initialiseAST(TokenStream* tokenStream){
	TOKEN programToken;
	programToken.type = NIL;
	programToken.value = "PROGRAM";
	AstNode programNode(programToken);
	AbstractSyntaxTree* AST = new AbstractSyntaxTree(programNode);

	bool isParsed = parseProgram(tokenStream, AST);

	if(isParsed) return *AST;
	throw "Invalid parser Error";
}

bool parseProgram(TokenStream* tokenStream, AbstractSyntaxTree* AST){
	if(!atLeastOneNonTerminal(tokenStream, AST)) return false;
	if(tokenStream->peekCurrent().type == END_OF_FILE){
		AstNode endFileNode = createNode(END_OF_FILE, "");
		AST->parentNode.setNextChild(endFileNode);
		return true;
	}else{
		return parseProgram(tokenStream, AST);
	}
	return false;
}

bool atLeastOneNonTerminal(TokenStream* tokenStream, AbstractSyntaxTree* AST){
	if(tokenStream->peekCurrent().type == END_OF_FILE) return true; 
	AstNode* dclNode = parseDeclaration(tokenStream);
	if(dclNode == NULL){
		if(!parseAssignment(tokenStream)){
			AstNode* printStm = parsePrintStatement(tokenStream);
			if(printStm == NULL){
				AstNode* operatorNode = parseOperatorStatement(tokenStream);
				if(operatorNode == NULL){
					return false;
				}else{
					AST->parentNode.setNextChild(*operatorNode);					
				}
			}else{
				AST->parentNode.setNextChild(*printStm);
			}
		}
	}else{
		AST->parentNode.setNextChild(*dclNode);
	}
	return true;
}

bool parseAssignment(TokenStream* tokenStream){
	if(!checkId(tokenStream->peekCurrent().type)) return false;
	
	if(checkAssign(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkNumber(tokenStream->peekNext().type) || checkId(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkOperator(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
		return parseOperatorExpression(tokenStream);
	}
	tokenStream->moveToNext();
	
	return true;
}

bool parseOperatorExpression(TokenStream* tokenStream){
	if(!checkOperator(tokenStream->peekCurrent().type)) return false;

	if(checkNumber(tokenStream->peekNext().type) || checkId(tokenStream->peekNext().type)){ 
		tokenStream->moveToNext();
	}else{
		return false;
	}

	if(checkOperator(tokenStream->peekNext().type)){
		tokenStream->moveToNext();		 
		return parseOperatorExpression(tokenStream);
	}
	tokenStream->moveToNext();	
	return true;
}

AstNode* parseDeclaration(TokenStream* tokenStream){
	AstNode* typeNode = checkType(tokenStream->peekCurrent());
	if(typeNode == NULL) return NULL;
	AstNode* idNode = checkId(tokenStream->peekNext());
	if(idNode != NULL){
		typeNode->setNextChild(*idNode);
		tokenStream->moveToNext();
	}else {
		return NULL;
	}
	tokenStream->moveToNext();	
	return typeNode;
}

AstNode* parsePrintStatement(TokenStream* tokenStream){
	AstNode* printNode = checkPrint(tokenStream->peekCurrent());
	if(printNode == NULL) return NULL;
	AstNode* idNode = checkId(tokenStream->peekNext());
	if(idNode == NULL){
		AstNode* numNode = checkNumber(tokenStream->peekNext());
		if(numNode == NULL){
			return NULL;
		}else{
			printNode->setNextChild(*numNode);
			tokenStream->moveToNext();				
		}
	}else{
		printNode->setNextChild(*idNode);
		tokenStream->moveToNext();		
	}
	tokenStream->moveToNext();
	return printNode;
}

AstNode* parseOperatorStatement(TokenStream* tokenStream){
	AstNode* node;
	AstNode* idNode = checkId(tokenStream->peekCurrent());
	if(idNode == NULL){
		AstNode* numberNode = checkNumber(tokenStream->peekCurrent());
		if(numberNode == NULL){
			return NULL;
		}else{
			node = numberNode;
		}
	}else{
		node = idNode;
	}
	AstNode* operatorNode = checkOperator(tokenStream->peekNext());
	if(operatorNode != NULL){
		operatorNode->setNextChild(*node); 
		tokenStream->moveToNext();
	}else{
		return NULL;
	}

	AstNode* nextNode;
	AstNode* nextIdNode = checkId(tokenStream->peekNext());
	if(nextIdNode == NULL){
		AstNode* nextNumberNode = checkNumber(tokenStream->peekNext());
		if(nextNumberNode  == NULL){
			return NULL;
		}else{
			nextNode =  nextNumberNode ;
		}
	}else{
		nextNode = nextIdNode;
	}

	if(nextNode != NULL){
		operatorNode->setNextChild(*nextNode);
		tokenStream->moveToNext();
	}else {
		return NULL;
	}
	tokenStream->moveToNext();
	return operatorNode;
}

bool checkOperator(TokenType tokenType){
	if(tokenType != PLUS && tokenType != MINUS) return false;
	return true;
}

AstNode* checkOperator(TOKEN token){
	if(token.type != PLUS && token.type != MINUS) return NULL;
	return new AstNode(token);
}

AstNode* checkPrint(TOKEN token){
	if(token.type != PRINT) return NULL;
	return new AstNode(token);
}

bool checkAssign(TokenType tokenType){
	if(tokenType != ASSIGN) return false;
	return true;	
}

bool checkNumber(TokenType tokenType){
	if(tokenType != INT_NUM && tokenType != FLOAT_NUM) return false;
	return true;
}

AstNode* checkNumber(TOKEN token){
	if(token.type != INT_NUM && token.type != FLOAT_NUM) return NULL;
	return new AstNode(token);
}

AstNode* checkType(TOKEN token){
	if(token.type == FLOAT_DCL || token.type == INT_DCL) {
		return new AstNode(token);
	}
	return NULL;
}

bool checkId(TokenType tokenType){
	if(tokenType != ID) return false;
	return true;
	
}

AstNode* checkId(TOKEN token){
	if(token.type != ID) return NULL;
	return new AstNode(token);
}
