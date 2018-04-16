#include <Scanner.h>
#include <string>
#include <Parser.h>
#include <TokenStream.h>
#include <vector>

int main(int argc, char** argv){
	TOKEN* tokenPtr;
	std::vector<TOKEN> tokens = scan(std::string(argv[1]));
	TokenStream* tokenStream = new TokenStream(tokens);
	
	bool parsed = parseProgram(tokenStream);
	std::cout << std::boolalpha;
	std::cout << "Parsed? "<< parsed << std::endl;
	return 0;
}