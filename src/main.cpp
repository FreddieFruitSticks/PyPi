#include <Scanner.h>
#include <string>
#include <Parser.h>
#include <vector>

int main(int argc, char** argv){
	TOKEN* tokenPtr;
	std::vector<TOKEN> tokens = scan(std::string(argv[1]));
	tokenPtr = &tokens[0];
	bool parsed = parseProgram(tokenPtr);
	std::cout << std::boolalpha;
	std::cout << "Parsed? "<< parsed << std::endl;
	return 0;
}