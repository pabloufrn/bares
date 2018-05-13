
/// Ler e insere na lista todas as expressões que estão organizadas por linhas no arquivo de entrada.
/// \param vetor com todas as expressões.
/// \param arquivo de entrada de dados.
void readConfig( sc::vector< std::string > & conj , arq_entrada & file_ ){

	std::string linha;

	/// Recebe e envia os dados da linha para o vetor.
	while( getline( file_ , linha ) ){
		conj.push_back( linha );
	}

}

/// Ler o arquivo de entrada.
/// \param nome do arquivo de entrada.
/// \param vetor para armazenar as expressões.
void readFile( std::string nomeArq , sc::vector<std::string> & conjunto ){
	
	std::cout << ">>> Trying to open input file [" + nomeArq + "]...";

	/// Cria tipo de arquivo de entrada.
	arq_entrada iFile;

	/// Abre o arquivo de entrada.
	iFile.open( nomeArq );

	/// Gera erro caso não foi possível abrir o arquivo de entrada.
	if( iFile.fail() ){

		std::cout << " error!\nTry again!\n";
		std::exit(1);

	}

	std::cout << " done!\n";

	std::cout << ">>> Processing data, please wait..." << std::endl;

	/// Realiza a leitura das linhas com as expressões.
	readConfig( conjunto , iFile );

	/// Fecha o arquivo de entrada.
	iFile.close();

}

