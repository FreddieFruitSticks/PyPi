#include <Scanner.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <regex>

std::ostream& operator << (std::ostream& o, const TOKEN& a){
	return o << "type: " << a.type << ", value: " << a.value;
}

TOKEN getReservedKeyword(std::string terminal){
	TOKEN token;

	if (terminal == "float"){
		token.type = "floatDcl";
	}else if(terminal == "int"){
		token.type = "intDcl";
	}else if(terminal == "print"){
		token.type = "print";
	}
	return token;
}

TOKEN getOperator(std::string terminal){
	TOKEN token;

	if (terminal == "="){
		token.type = "assign";
	}else if (terminal == "+"){
		token.type = "plus";
	}else if (terminal == "-"){
		token.type = "minus";
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
	if (token.type != ""){
		return token;
	}
	token = getOperator(terminal);
	if(token.type != ""){
		return token;
	}

	if (std::regex_match(terminal, std::regex("_?[_0-9a-zA-Z]+"))){
		token.type = "id";
		token.value = terminal;
	}else if (std::regex_match(terminal, std::regex("[1-9][0-9]*"))){
		token.type = "intNum";
		token.value = terminal;
	}else if(std::regex_match(terminal, std::regex("[0-9]+[.][0-9]+"))){
		token.type = "floatNum";
		token.value = terminal;
	}
	return token;
};

void printVector(std::vector<TOKEN> tokens){
	std::vector<TOKEN>::iterator tokensIterator;
	for(tokensIterator = tokens.begin(); tokensIterator != tokens.end(); tokensIterator++){
		std::cout << *tokensIterator << std::endl;
	}
}

#define NEWLINE 32
#define SPACE 10

TOKEN* scan(std::string source) {
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
		if((int)nextChar == NEWLINE || (int)nextChar == SPACE){
			if(tokenBuffer.size() > 0){
				tokens.push_back(getToken(tokenBuffer));
			}
			tokenBuffer.clear();
			continue;
		}

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
	endToken.type = "$";
	tokens.push_back(endToken);
	printVector(tokens);
	return &tokens.front();
}

