#include <string>
#include <iostream>

#ifndef _SCANNER_H
#define _SCANNER_H
struct TOKEN {
	std::string type;
	std::string value;
};
TOKEN* scan(std::string);
std::ostream& operator << (std::ostream& o, const TOKEN& a);
#endif /*_SCANNER_H*/