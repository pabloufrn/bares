#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream> // cout, cin
#include <iterator> // std::distance()
#include <vector>   // sc::vector
#include <sstream>  // std::istringstream
#include <cstddef>  // std::ptrdiff_t
#include <limits>   // std::numeric_limits, para validar a faixa de um inteiro.
#include <algorithm>// std::copy, para copiar substrings.

#include "token.h"  // struct Token.

/*!
 * Implements a recursive descendent parser for a EBNF grammar.
 *
 * This class also tokenizes the input expression into its components, creating a list of tokens.
 *
 * The EBNF grammar is:
 * ```
 *   <expr>            := <term>,{ ("+"|"-"|"*"|"/"|"%"|"^"),<term> };
 *   <term>            := "(", <expr>, ")" | <integer>;
 *   <integer>         := 0 | ["-"],<natural_number>;
 *   <natural_number>  := <digit_excl_zero>,{<digit>};
 *   <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
 *   <digit>           := "0"| <digit_excl_zero>;
 * ```
 */
class Parser
{
    public:
        /// Este struct representa o resultado da operação de parsing (transformação).
        struct ResultType
        {
            //=== Alias
            typedef std::ptrdiff_t size_type; //!< Usado para a localização da coluna determinada.
            
            /// Lista de possíveis erros sintáticos.
            enum code_t {
                OK = 0, //!< Expressão está correta.
                INTEGER_OUT_OF_RANGE,
                MISSING_TERM,
                EXTRANEOUS_SYMBOL,
                ILL_FORMED_INTEGER,
                MISSING_CLOSE,
                UNEXPECTED_END_OF_EXPRESSION,
            };
            
            //=== Membros (publicos).
            code_t type;      //!< Código de erro.
            size_type at_col; //!< Armazena em qual coluna ocorreu o erro.
            
            /// Contrutor default.
            explicit ResultType( code_t type_=OK , size_type col_=0u )
            : type{ type_ }
            , at_col{ col_ }
            { /* vazio */ }
            
            /// Sobrecarga do operador de igualdade.
            bool operator==( ResultType & tipo ){
                return type == tipo.type;
            }
            
            /// Sobrecarga do operador de diferença.
            bool operator!=( ResultType tipo ){
                return type != tipo.type;
            }
        };
        
        //==== Aliases
        typedef short int required_int_type; //!< O tipo interiro que nós aceitamos como válida para uma expressão.
        typedef long long int input_int_type; //!< O tipo interiro que lê para a entrada (maior do que o int).
        
        //==== Interface pública.
        /// Parses e tokenizes  de entrada do código da expressão. Retorna o resultado como um struct.
        ResultType parse( std::string e_ );
        /// Recupera a lista de tokens criada durante o processo de parsing.
        sc::vector< Token > get_tokens( void ) const;
        
        //==== Métodos especiais.
        /// Contrutor default.
        Parser() = default;
        /// Descontrutor default.
        ~Parser() = default;
        /// Desliga o construtor de cópia, já que não precisaremos dele.
        Parser( const Parser & ) = delete;  // Construtor cópia.
        /// Desliga o operador de atribuição.
        Parser & operator=( const Parser & ) = delete; // Atribuição.
        
        
        
    private:
        // Terminal de simbolos.
        enum class terminal_symbol_t{  // Os simbolos:-
            TS_PLUS,	        //!< código para "+"
            TS_MINUS,	        //!< código para "-"
            TS_TIMES,           //!< código para "*"
            TS_DIVIDED,         //!< código para "/"
            TS_PERCENT,         //!< código para "%"
            TS_POWER,           //!< código para "^"
            TS_OPEN,            //!< código para "("
            TS_CLOSE,           //!< código para ")"
            TS_ZERO,            //!< código para "0"
            TS_NON_ZERO_DIGIT,  //!< código para os digitos "1"->"9"
            TS_WS,              //!< código para o espaço em branco
            TS_TAB,             //!< código para tab
            TS_EOS,             //!< código para o fim da string
            TS_INVALID	        //!< token invalido
        };
        
        //==== Membros privados.
        std::string expr;                //!< Expressão para ser "parsed"
        std::string::iterator it_curr_symb; //!< Ponteiro para o char padrão dentro da expressão.
        sc::vector< Token > token_list; //!< Lista de resultado da lista de token extraidas da expressão.
        
        terminal_symbol_t lexer( char c_ ) const;
        //std::string token_str( terminal_symbol_t s_ ) const;
        
        //=== Métodos suportados.
        void next_symbol( void );                // Avançar o iterador para o proximo caractere da expressão.
        bool peek( terminal_symbol_t c_ ) const; // Verificar o atual caractere.
        bool accept( terminal_symbol_t c_ );     // Tentar aceitar o simbolo informado.
        bool expect( terminal_symbol_t c_ );        // Pular qualquer espaço em branco ou tabs e tentar aceitar o próximo caractere.
        void skip_ws( void );                    // Pular qualquer espaço em branco ou tab e parar no próximo caractere.
        bool end_input( void ) const;            // Verificar quando encontrarmos o fim da expressão.
        
        //=== Métodos NTS.
        ResultType expression();
        ResultType term();
        ResultType integer();
        ResultType natural_number();
        bool digit_excl_zero();
        bool digit();
};

#include "parser.inl"

#endif
