#include <Scanner.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <regex>

TOKEN getReservedKeyword(std::string terminal){
	TOKEN token;

	if (terminal == "float"){
		token.type = FLOAT_DCL;
	}else if(terminal == "int"){
		token.type = INT_DCL;
	}else if(terminal == "print"){
		token.type = PRINT;
	}
	return token;
}

TOKEN getOperator(std::string terminal){
	TOKEN token;

	if (terminal == "="){
		token.type = ASSIGN;
	}else if (terminal == "+"){
		token.type = PLUS;
	}else if (terminal == "-"){
		token.type = MINUS;
	}
	return token;
}

bool checkOperator(char op){
	switch(op){
		case '=': return true; break;
		case '+': return true; break;
		case '-': return true; break;
		default: return false; break;
	}
}

TOKEN getToken(std::vector<char> tokenBuffer){
	TOKEN token;
	std::string terminal = "";
	for(int i = 0; i < tokenBuffer.size(); i++){
		terminal += tokenBuffer[i];
	}

	token = getReservedKeyword(terminal);
	if (token.type != NIL){
		return token;
	}
	token = getOperator(terminal);
	if(token.type != NIL){
		return token;
	}

	if (std::regex_match(terminal, std::regex("[1-9][0-9]*"))){
		token.type = INT_NUM;
		token.value = terminal;
	}else if (std::regex_match(terminal, std::regex("_?[_0-9a-zA-Z]+"))){
		token.type = ID;
		token.value = terminal;
	}else if(std::regex_match(terminal, std::regex("[0-9]+[.][0-9]+"))){
		token.type = FLOAT_NUM;
		token.value = terminal;
	}
	return token;
};

void printVector(TOKEN* tokens){
	TOKEN* tokenPtr = tokens;
	TOKEN* tokensIterator;
	for(tokensIterator = tokenPtr; tokensIterator->type != END_OF_FILE; tokensIterator++){
		std::cout << *tokensIterator << std::endl;
	}
	std::cout << *tokensIterator << std::endl;	
}

#define NEWLINE_CONST 32
#define SPACE_CONST 10

std::vector<TOKEN> scan(std::string source) {
	std::ifstream sourceIn(source.c_str());
	std::vector<TOKEN> tokens;
	std::vector<char> tokenBuffer;
	while(char nextChar = sourceIn.get()){
		if(sourceIn.eof() || (int)nextChar == -1){
			if(tokenBuffer.size() > 0){
				tokens.push_back(getToken(tokenBuffer));
			}
			tokenBuffer.clear();
			break;
		}
		if(nextChar == NEWLINE_CONST || nextChar == SPACE_CONST){
			if(tokenBuffer.size() > 0){
				tokens.push_back(getToken(tokenBuffer));
			}
			tokenBuffer.clear();
			continue;
		}

		// Checking to see if we need to ignore white spaces. eg a ( can have many white spaces before and after it
		if(checkOperator(nextChar)){
			if(tokenBuffer.size() > 0){
				tokens.push_back(getToken(tokenBuffer));
			}
			tokenBuffer.clear();
			tokenBuffer.push_back(nextChar);
			tokens.push_back(getToken(tokenBuffer));
			tokenBuffer.clear();
			continue;				
		}
		tokenBuffer.push_back(nextChar);
	}
	TOKEN endToken;
	endToken.type = END_OF_FILE;
	tokens.push_back(endToken);
	TOKEN* tokenPtr = &tokens[0];
	// printVector(firstToken);
	// std::cout << firstToken->type << std::endl;
	
	return tokens;
}
#undef NEWLINE_CONST
#undef SPACE_CONST

std::ostream& operator << (std::ostream& out, const TokenType& value){
	static std::map<const TokenType, std::string> tokens;
	#define INSERT_TOKEN_NAME(p) tokens[p] = #p
		INSERT_TOKEN_NAME(NIL);
        INSERT_TOKEN_NAME(END_OF_FILE);
        INSERT_TOKEN_NAME(FLOAT_DCL);
        INSERT_TOKEN_NAME(INT_DCL);
        INSERT_TOKEN_NAME(PRINT);
        INSERT_TOKEN_NAME(ASSIGN);
        INSERT_TOKEN_NAME(PLUS);
        INSERT_TOKEN_NAME(MINUS);
        INSERT_TOKEN_NAME(ID);
        INSERT_TOKEN_NAME(INT_NUM);
        INSERT_TOKEN_NAME(FLOAT_NUM);
	#undef INSERT_TOKEN_NAME

	return out << tokens[value];
}

std::ostream& operator << (std::ostream& out, const TOKEN& value){
	return out << "type: " << value.type << ", value: " << value.value;
}