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

// Simple helper functions that identify the incoming symbol.
bool is_operator( symbol_type s )
{ return s == Token::token_t::OPERATOR; }

bool is_operand( symbol_type s )
{ return s == Token::token_t::OPERAND; }

bool is_opening_scope( symbol_type s )
{ return s == Token::token_t::PARENTHESIS_OPEN; }

bool is_closing_scope( symbol_type s )
{ return s == Token::token_t::PARENTHESIS_CLOSE; }

/// Converts a expression in infix notation to a corresponding profix representation.
void infix_to_postfix( std::vector<Token> &, std::vector<Token> & );

/// Converts a char (1-digit operand) into an integer.
value_type char2integer( char c )
{ return c-'0'; }

/// Converts a string to an integer
value_type string2int( std::string s )
{	
	value_type number = 0;
	bool negative = false;
	for( char & c : s )
		if( c == '-' )
			negative = true;
		else
			number = number * 10 + char2integer(c);
	if(negative)
		return -number;		
	return number;
}


/// Check the operand's type of association.
bool is_right_association( std::string op )
{ return op == "^"; }


/// Change an infix expression into its corresponding postfix representation.
value_type evaluate_postfix( std::vector<Token> & );

/// Returns the precedence value (number) associated with an operator.
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

/// Determines whether the first operator is >= than the second operator.
bool has_higher_or_eq_precedence( std::string op1 , std::string op2 )
{
	return ( get_precedence(op1) >= get_precedence(op2) ) ?
		is_right_association( op1 ) ? false : true  :
		false;
}
/// Execute the binary operator on two operands and return the result.
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

int resolucao( std::vector<Token> & expression_ )
{
	std::vector< Token > postfix;

	infix_to_postfix( expression_ , postfix);
    
	auto result = evaluate_postfix( postfix );
    
	return result;
}

void infix_to_postfix( std::vector< Token > & infix, std::vector<Token> & postfix )
{
    pl::stack< Token > s; // auxiliary data structure.
    
    // Process each incoming symbol
    for( const auto & symbol : infix )
    {
        // operando entra de qualquer jeito
        if ( is_operand( symbol.type ) )
        {
            postfix.push_back( symbol ); // send it straight to the output symbol queue.
        }
        else if ( is_opening_scope( symbol.type ) )
        {
            s.push( symbol ); // always goes into the "waiting room"
        }
        else if ( is_closing_scope( symbol.type ) )
        {
            // Pop out all pending operations.
            while( not is_opening_scope( s.top().type ) )
            {
                // remove operator and send it to the postfix expression.
                postfix.push_back( s.top() );
                s.pop();
            }
            // Don't forget to get rid of the opening scope.
            s.pop();
        }
        else if ( is_operator( symbol.type ) )
        {
            // Send out the "waiting" operator with higher or equal precedence...
            // unless they have equal precedence AND are right associated.
            while ( not s.empty() and has_higher_or_eq_precedence( s.top().value, symbol.value ) )
            {
                postfix.push_back(s.top()); // send it to the output
                s.pop(); // get rid of the operator.
            }
            // The incoming symbol always goes into the "waiting room".
            s.push( symbol ) ;
        }
    }
    
    // Clear out any pending operators stored in the stack.
    while ( not s.empty() )
    {
        postfix.push_back(s.top());
        s.pop();
    }
    
}

value_type evaluate_postfix( std::vector<Token> & postfix )
{
	pl::stack< value_type > s;
	// process operands
	// precondition: the postfix is valid
	for ( const auto & symbol : postfix)
	{
		if( is_operand( symbol.type ) ){
			s.push ( string2int( symbol.value ) );
		} else if(is_operator( symbol.type )){
			auto op2 = s.top(); s.pop();
			auto op1 = s.top(); s.pop();
			// The result of the operation is pushed back into the stack.
			s.push(execute_operator(op1, op2, symbol.value)) ;
		} else{
			assert(false);
		}
	}

	return s.top();
}
