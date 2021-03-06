/**
 *  @file main.cpp
 *
 *  @brief This file is the main function of this compiler. 
 */
#include <iostream>
#include <cstdlib>
#include "codegen/codegen.hpp"
using namespace std;

ParsingTree pt;
SymbolTable symbolTable;
extern int yyparse(char*);
extern FILE* yyin;

int main(int argc,char* argv[])
{
	if(!(yyin=fopen(argv[1],"r")))
	{
		cerr<<"File not exist.\n";
		exit(-1);
	}

	if(yyparse(argv[2])) exit(1);
	//else cout<<"successed.\n";

	#ifdef DEBUG
	pt.printTree(argv[2]);
	#endif

	string name;
	#ifdef DEBUG
	if(argc == 4)
		name = string(argv[3]);
	#else
	if(argc == 3)
		name = string(argv[2]);
	#endif
	else
	{
		cerr<<"No output file name\n";
		cin>>name;
	}
	CodeGenContext context(name);
	context.generateCode(pt);

	return 0;
}
