#include <Scanner.h>
#include <string>
#include <Parser.h>

int main(int argc, char** argv){
	TOKEN* tokenPtr;
	tokenPtr = scan(std::string(argv[1]));
	bool parsed = parseProgram(tokenPtr);
	std::cout << std::boolalpha;
	std::cout << "Parsed? "<< parsed << std::endl;
	return 0;
}