#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>

typedef enum Tokens {
	NIL,
	END_OF_FILE,
	FLOAT_DCL,
	INT_DCL,
	PRINT,
	ASSIGN,
	PLUS,
	MINUS,
	ID,
	INT_NUM,
	FLOAT_NUM
} TokenType;

struct TOKEN {
	TokenType type = NIL;
	std::string value;
};

TOKEN* scan(std::string);
std::ostream& operator << (std::ostream& o, const TOKEN& a);
std::ostream& operator << (std::ostream& out, const TokenType& value);
#endif /*_SCANNER_H*/