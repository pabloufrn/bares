/*!
 * Converts an arithmetic expression in infix notation into postfix
 * representation. After the convertion is successfyly done, the
 * program evaluates the expression based on stacks and queues.
 *
 * Input Postfix expression must be in a desired format.
 * Operands and operator, **both must be single character**.
 * Only '+', '-', '*', '%', '/', and '^' (for exponentiation) operators are expected;
 * Any other character is just ignored.
 */

#include <iostream>  // cout, endl
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error
#include <queue>

//=== Aliases
using value_type = short int;            //!< Type we operate on.
using symbol_type = Token::token_t;
using input_int_type = long long int;   //!< The integer type that we read from the input (larger thatn the required int).

// Verifica se é um operado.
bool is_operator( symbol_type s )
{ return s == Token::token_t::OPERATOR; }

/// Vericica se é um operando.
bool is_operand( symbol_type s )
{ return s == Token::token_t::OPERAND; }

/// Verifica se é um parentese aberto.
bool is_opening_scope( symbol_type s )
{ return s == Token::token_t::PARENTHESIS_OPEN; }

/// Verifica se é um parentese fechando.
bool is_closing_scope( symbol_type s )
{ return s == Token::token_t::PARENTHESIS_CLOSE; }

/// Converte uma expressão na notação infix para uma profix.
void infix_to_postfix( sc::vector<Token> &, sc::vector<Token> & );

/// Converte uma string para inteiro.
value_type string2int( std::string s )
{	
    value_type number = 0;
    bool negative = false;

    for( char & c : s ){
        if( c == '-' )
            negative = true;
        else
            number = number * 10 + char2integer(c);
    }
    if(negative)
        return -number;		
    return number;
}


/// Verifica se tem mais de  um ^ seguido.
bool is_right_association( std::string op )
{ return op == "^"; }


/// Modifica uma expressão infix para uma posfix.
value_type evaluate_postfix( sc::vector<Token> & );

/// Retorna um valor de precedência de cada operador.
short get_precedence( std::string op )
{
    if(op == "^")
        return 4;
    else if( op == "*" || op == "/" ) 
        return 3;
    else if( op == "%" )
        return 2;
    else if( op == "+" || op == "-")
        return 1;
    else if( op == "(" )
        return 0;
    else
        return -1;
}

/// Determina qual é o primeiro e o segundo operador por comparação de maior ou igual.
bool has_higher_or_eq_precedence( std::string op1 , std::string op2 )
{
    return ( get_precedence(op1) >= get_precedence(op2) ) ?
    is_right_association( op1 ) ? false : true  :
    false;
}
/// Executa a operação binária entre dois operandos retornando o resultado da operação.
value_type execute_operator( value_type v1, value_type v2, std::string op )
{
    input_int_type result;
    if( op == "^")
        result = pow( v1, v2 );
    else if( op == "*")
        result = v1 * v2;
    else if( op == "/"){
        if ( v2 == 0 ){
            throw std::runtime_error("Division by zero!");
        }
        result = v1/v2;
    }
    else if( op == "%"){
        if ( v2 == 0 ) {
            throw std::runtime_error("Division by zero!");
        }
        result = v1%v2;
    }
    else if( op == "+")
        result = v1+v2;
    else if( op == "-")
        result = v1-v2;
    if( result < std::numeric_limits< value_type >::min() or \
        result > std::numeric_limits< value_type >::max()    )
        throw std::runtime_error("Numeric overflow error!");
    return result;
    
}

/// Realiza as operações.
/// \param expressão.
/// \return Retorna o resultado da expressão.
int resolucao( sc::vector<Token> & expression_ )
{
    sc::vector< Token > postfix;
    
    infix_to_postfix( expression_ , postfix);
    
    auto result = evaluate_postfix( postfix );
    
    return result;
}

/// Converte a notação infix de uma expressão para a postfix.
void infix_to_postfix( sc::vector< Token > & infix, sc::vector<Token> & postfix )
{
    pl::stack< Token > s; // Estrutura de dado auxiliar.
    
    // Processa cada symbolo.
    for( const auto & symbol : infix )
    {
        // operando entra de qualquer jeito
        if ( is_operand( symbol.type ) )
        {
            postfix.push_back( symbol ); // envia o simbolo para a fila de simbolos de saída.
        }
        else if ( is_opening_scope( symbol.type ) )
        {
            s.push( symbol ); // sempre coloca na "lista de espera".
        }
        else if ( is_closing_scope( symbol.type ) )
        {
            // Remove todas as operações pendentes.
            while( not is_opening_scope( s.top().type ) )
            {
                // Remove o operador e envia para a expresão postfix.
                postfix.push_back( s.top() );
                s.pop();
            }
            // Remove o parentese aberto de dentro da pilha.
            s.pop();
        }
        else if ( is_operator( symbol.type ) )
        {
            // Sai os operadores que estão esperando com precedencia maior ou igual.
            while ( not s.empty() and has_higher_or_eq_precedence( s.top().value, symbol.value ) )
            {
                postfix.push_back(s.top()); // envia para a saída.
                s.pop(); // remove o operaodr.
            }
            // O simbolo sempre vai para a sala de espera caso seja menor.
            s.push( symbol ) ;
        }
    }
    
    // Remove qualquer operador que esteja na fila.
    while ( not s.empty() )
    {
        postfix.push_back(s.top());
        s.pop();
    }
    
}

/// Realiza as operações.
/// \param vetor com a expressão.
/// \return retorna o resultado da expressão.
value_type evaluate_postfix( sc::vector<Token> & postfix )
{
    pl::stack< value_type > s;
    // processamento dos operandos.
    // precondição: a expressão postfix é válida.
    for ( const auto & symbol : postfix)
    {
        /// Realiza verificação se é operando ou operador.
        if( is_operand( symbol.type ) ){
            /// Insere na pilha o operando
            s.push ( string2int( symbol.value ) );
        } else if(is_operator( symbol.type )){
            /// Armazena os valores do topo e remove eles da pilha.
            auto op2 = s.top(); s.pop();
            auto op1 = s.top(); s.pop();
            // O resultado da operação é inserida de volta na pilha.
            s.push(execute_operator(op1, op2, symbol.value)) ;
        } else{
            assert(false);
        }
    }
    
    /// Retorna o topo da pilha que é o resultado da expressão.
    return s.top();
}
