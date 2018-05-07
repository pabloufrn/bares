#include <iostream>
#include <fstream>
#include <string>

using arq_entrada = std::ifstream;
using arq_saida = std::ofstream;

#include "../include/vector.h"
#include "../include/stack.h"
#include "../include/imp_driver.h"

int main( int argc, char* argv[]){

	if( argc < 2){
		std::cout << "ERROR! Wrong syntaxe!\n$./bares < input_file > [ output_file ]\n";
		return -1;
	}

	sc::vector < std::string > conjunto;

	std::string entrada = argv[1];

	readFile(  entrada , conjunto );

	if( argc == 3 ){
		outputFile( argv[2] );
	}

	return 0;
}