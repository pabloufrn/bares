#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error

//=== Aliases
using value_type = long int; //!< Type we operate on.
using arq_entrada = std::ifstream;
using arq_saida = std::ofstream;

#include "../include/vector.h"
#include "../include/stack.h"
#include "../include/fila.h"
#include "../include/imp_driver.h"
#include "../include/parser.h"
#include "../include/sbares.h"
#include "../include/extend_parser.h"

int main( int argc, char* argv[]){

	if( argc < 2){
		std::cout << "ERROR! Wrong syntaxe!\n$./bares < input_file > [ output_file ]\n";
		return -1;
	}

	sc::vector < std::string > conjunto;

	std::string entrada = argv[1];

	readFile(  entrada , conjunto );

	if( argc == 3 ){
		parser_driver_out(conjunto, argv[2]);
		//outputFile( argv[2] );
	} else{
		parser_driver( conjunto );
	}

	return 0;
}