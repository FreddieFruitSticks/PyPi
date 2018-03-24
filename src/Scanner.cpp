#include <Scanner.h>
#include <iostream>
#include <fstream>

void scan(std::string source) {
	std::ifstream sourceIn(source.c_str());
	std::string line;
	while(char nextChar = sourceIn.get()){
		if(sourceIn.eof()){
			break;
		}
		
		std::cout << std::hex << (int)nextChar << std::endl;
	}
	return;
}