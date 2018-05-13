

std::string print_error_msg( const Parser::ResultType & result, std::string str )
{
    std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    error_indicator[result.at_col] = '^';

    std::stringstream ss;
    std::string mensagem_error;

    switch ( result.type )
    {
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Integer constant out of range beginning at column ("<< result.at_col << ")!\n";
            return"Integer constant out of range beginning at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::MISSING_TERM:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Missing <term> at column (" << result.at_col << ")!\n";
            return  "Missing <term> at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            return  "Extraneous symbol after valid expression found at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::ILL_FORMED_INTEGER:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Ill formed integer at column (" << result.at_col << ")!\n";
            return   "Ill formed integer at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::MISSING_CLOSE:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Missing closing ”)”at column (" << result.at_col << ")!\n";
            return  "Missing closing ”)”at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            ss << result.at_col;
            ss >> mensagem_error;
            std::cout << "Unexpected end of input at column (" << result.at_col << ")!\n";
            return  "Unexpected end of input at column (" + mensagem_error + ")!\n";
        case Parser::ResultType::DIVISION_ZERO:
            std::cout << "Division by zero!\n";
            return  "Division by zero!\n";
        case Parser::ResultType::NUMERIC_OVERFLOW:
            std::cout << "Numeric overflow error!\n";
            return  "Numeric overflow error!\n";
        default:
            std::cout << "Unhandled error found!\n";
            return "Unhandled error found!\n";
    }

    //std::cout << "\"" << str << "\"\n";
    //std::cout << " " << error_indicator << std::endl;
}


void parser_driver( sc::vector<std::string> & conjunto ){
    

    Parser type_parser; // Instancia um parser.

    // Tentar analisar cada expressão da lista.
    for( const auto & express : conjunto )
    {
        // Fazer o parsing desta expressão.
        auto result = type_parser.parse( express );
        // Preparar cabeçalho da saida.
        std::cout << std::setfill('=') << std::setw(80) << "\n";
        std::cout << std::setfill(' ') << ">>> Parsing \"" << express << "\"\n";
        // Se deu pau, imprimir a mensagem adequada.
        if ( result.type != Parser::ResultType::OK ){
            std::string error_name = print_error_msg( result, express );
        }
        else{
            std::cout << ">>> Expression SUCCESSFULLY parsed!\n";
        

            // Recuperar a lista de tokens.
            auto lista = type_parser.get_tokens();
            //std::cout << ">>> Tokens: { ";
            //std::copy( lista.begin(), lista.end(),
            //        std::ostream_iterator< Token >(std::cout, " ") );
            //std::cout << "}\n";

            int valor = resolucao( lista );

            if(valor > 32767 || valor < -32768 ){
                result.type = Parser::ResultType::NUMERIC_OVERFLOW;
                std::string error_name = print_error_msg( result, express );
            }
            else
                std::cout << valor;
        }
    }

    std::cout << "\n>>> Normal exiting...\n";
}

void parser_driver_out( sc::vector<std::string> & conjunto , std::string ofFile_name ){
    
    arq_saida oFile;
    oFile.open(ofFile_name);
    

    if( oFile.fail()){
        std::cout << "Error! It wasn't possible to create the output file.\n";
        exit(1);
    }

    Parser type_parser; // Instancia um parser.

    // Tentar analisar cada expressão da lista.
    for( const auto & express : conjunto )
    {
        // Fazer o parsing desta expressão.
        auto result = type_parser.parse( express );
        // Preparar cabeçalho da saida.
        std::cout << std::setfill('=') << std::setw(80) << "\n";
        std::cout << std::setfill(' ') << ">>> Parsing \"" << express << "\"\n";
        // Se deu pau, imprimir a mensagem adequada.

        std::cout << "Expressão : " << express << std::endl;

        if ( result.type != Parser::ResultType::OK ){
            
            std::string error_name = print_error_msg( result, express );
            oFile << error_name;

        }
        else{
            std::cout << ">>> Expression SUCCESSFULLY parsed!\n";
        

            // Recuperar a lista de tokens.
            std::vector<Token> lista = type_parser.get_tokens();
            //std::cout << ">>> Tokens: { ";
        
            /*std::string teste;
            auto f (lista.begin());
            auto i(0);
            while( f+i != lista.end() ){
                teste += lista[i].value;
                ++i;
            }*/
            //std::copy( lista.begin(), lista.end(),
            //        std::ostream_iterator< Token >(teste, "+") );
            int valor = resolucao(lista);
            
            if(valor > 32767 || valor < -32768 ){
                result.type = Parser::ResultType::NUMERIC_OVERFLOW;
                std::string error_name = print_error_msg( result, express );
                oFile << error_name << std::endl;
            }
            else
                oFile << valor << std::endl;
            //std::cout << "}\n";
        }


    }

    oFile.close();


    std::cout << "\n>>> Normal exiting...\n";
}