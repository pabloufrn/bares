void readConfig( sc::vector< std::string > & conj , arq_entrada & file_ ){

	std::string linha;

	while( getline( file_ , linha ) ){
		conj.push_back( linha );
	}

}

void readFile( std::string nomeArq , sc::vector<std::string> & conjunto ){
	
	std::cout << ">>> Trying to open input file [" + nomeArq + "]...";

	arq_entrada iFile;

	iFile.open( nomeArq );

	if( iFile.fail() ){

		std::cout << " error!\nTry again!\n";
		std::exit(1);

	}

	std::cout << " done!\n";

	std::cout << ">>> Processing data, please wait..." << std::endl;

	readConfig( conjunto , iFile );

	iFile.close();

}


/*
 ---------- ARQUIVO DE SAÍDA --------

void outputFile( std::string nomeArq ){

}*/