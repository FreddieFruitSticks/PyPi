#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <vector>

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

std::vector<TOKEN> scan(std::string);
std::ostream& operator << (std::ostream& o, const TOKEN& a);
std::ostream& operator << (std::ostream& out, const TokenType& value);
inline bool operator==(const TOKEN& lhs, const TOKEN& rhs){
	if(lhs.type == rhs.type){
		if (lhs.value == rhs.value) return true;
	}
	return false;
}
#endif /*_SCANNER_H*/