#include <Parser.h>
#include <TestScanner.h>
#include <TestParser.h>
#include <TestAST.h>

int main(int argc, char** argv){
	scanner_suite();
	parser_suite();
	AST_suite();
}