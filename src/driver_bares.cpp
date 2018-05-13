#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error

//=== Aliases
using arq_entrada = std::ifstream;
using arq_saida = std::ofstream;

#include "../include/vector.h"
#include "../include/stack.h"
#include "../include/fila.h"
#include "../include/imp_driver.h"
#include "../include/parser.h"
#include "../include/sbares.h"
#include "../include/extend_parser.h"


/// Função principal
int main( int argc, char* argv[]){

	/// Verifica se o usuário inseriu os argumentos.
	if( argc < 2){
		std::cout << "ERROR! Wrong syntaxe!\n$./bares < input_file > [ output_file ]\n";
		return -1;
	}

	/// Cria vetor para armazenar cada linha do arquivo de entrada.
	sc::vector < std::string > conjunto;

	/// Salva o nome do arquivo de entrada.
	std::string entrada = argv[1];

	/// Verifica a leitura do arquivo de entrada.
	readFile(  entrada , conjunto );

	/// Verifica se o usuário colocou algum arquivo de entrada.
	if( argc == 3 ){
		/// Executa a função que realiza o processamento sobre as expressões com arquivo de saída.
		parser_driver_out(conjunto, argv[2]);
	} else{
		/// Executa a função que realiza o processamento sobre as expressões sem arquivo de saída.
		parser_driver( conjunto );
	}

	/// Finaliza o programa.
	return 0;
}
