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
//#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error

#include "../include/stack.h"		// stack

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

// Simple helper functions that identify the incoming symbol.
bool is_operator( symbol s )
{ return std::string("^*%/+-").find( s ) != std::string::npos; }

bool is_operand( symbol s )
{ return s>='0' and s<='9'; }

bool is_opening_scope( symbol s )
{ return s == '(' ; }

bool is_closing_scope( symbol s )
{ return s == ')' ; }

bool is_splitter( symbol s )
{ return s == ' ' ; }
/// Converts a expression in infix notation to a corresponding profix representation.
std::string infix_to_postfix( std::string );

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
bool is_right_association( symbol op )
{ return op == '^'; }


/// Change an infix expression into its corresponding postfix representation.
value_type evaluate_postfix( std::string );

/// Returns the precedence value (number) associated with an operator.
short get_precedence( symbol op )
{
	switch( op )
	{
		case '^': return 4;

		case '*': return 3;
		case '/': return 3;

		case '%': return 2;

		case '+': return 1;
		case '-': return 1;

		case '(': return 0;

		default: assert(false);
	}
	return -1;
}

/// Determines whether the first operator is >= than the second operator.
bool has_higher_or_eq_precedence( symbol op1 , symbol op2 )
{
	return ( get_precedence(op1) >= get_precedence(op2) ) ?
		is_right_association( op1 ) ? false : true  :
		false;

}
/// Execute the binary operator on two operands and return the result.
value_type execute_operator( value_type v1, value_type v2, symbol op )
{
	switch( op )
	{
		case '^':
			return pow( v1, v2 );
		case '*':
			return v1 * v2;
		case '/':
			if ( v2 == 0 ) throw std::runtime_error("Division by zero");
			return v1/v2;
		case '%':
			if ( v2 == 0 ) throw std::runtime_error("Division by zero");
			return v1%v2;
		case '+':
			return v1+v2;
		case '-':
			return v1-v2;
		default:
			throw std::runtime_error("Invalid operator!");
	}
}

int resolucao( std::string expression )
{

	auto postfix = infix_to_postfix(expression);
	std::cout << ">>> Input (infix)    = " << expression << "\n";
	std::cout << ">>> Output (postfix) = " << postfix << "\n";

	auto result = evaluate_postfix( postfix );
	std::cout << ">>> Result is: " << result << std::endl;
	std::cout << "\n>>> Normal exiting...\n";
	return result;
}

std::string infix_to_postfix( std::string infix )
{
	pl::stack< symbol > s; // auxiliary data structure.
	std::string postfix; // stores the postfix expression
	bool start_operand = true; // if true next character is the beginning of a number
	// Process each incoming symbol
	for( const auto & c : infix )
	{
		if(start_operand)
		{
			postfix += c; // stores whatever character it is.
			start_operand = false; // the beginning of the number was stored already,
		}
		else if ( is_operand( c ) )
			postfix += c; // send it straight to the output symbol queue.
		else if ( is_opening_scope( c ) )
		{
			s.push( c ); // always goes into the "waiting room"
			start_operand = true;
		}
		else if ( is_closing_scope( c ) )
		{
			postfix += ' ';
			// Pop out all pending operations.
			while( not is_opening_scope( s.top() ) )
			{
				// remove operator and send it to the postfix expression.
				postfix += s.top();
				s.pop();
			}
			// Don't forget to get rid of the opening scope.
			s.pop();
		}
		else if ( is_operator( c ) )
		{
			postfix += ' ';
			// Send out the "waiting" operator with higher or equal precedence...
			// unless they have equal precedence AND are right associated.
			while ( not s.empty() and has_higher_or_eq_precedence( s.top(), c ) )
			{
				postfix += s.top(); // send it to the output
				s.pop(); // get rid of the operator.
			}
			// The incoming symbol always goes into the "waiting room".
			s.push( c ) ;
		}
		else // white space or whatever
		{
			// Do nothing. Just ignore this...
		}
	}

	// Clear out any pending operators stored in the stack.
	while ( not s.empty() )
	{
		postfix += s.top();
		s.pop();
	}

	return postfix;
}

value_type evaluate_postfix( std::string postfix )
{
	pl::stack< value_type > s;
	// process operands
	std::string::size_type index_begin = 0, index_end = postfix.find( ' ' , index_begin );
	// precondition: the postfix is valid
	while( index_end != std::string::npos )
	{
		s.push ( string2int( postfix.substr( index_begin , index_end - index_begin ) ) );
		index_begin = index_end + 1;
		index_end = postfix.find( ' ' , index_begin );
	}

	postfix = postfix.substr( index_begin );

	for( const auto & c : postfix )
	{
		if ( is_operator( c ) )
		{
			// IMPORTANT: Pop out operandos in reverse order!
			auto op2 = s.top(); s.pop();
			auto op1 = s.top(); s.pop();
			// The result of the operation is pushed back into the stack.
			s.push( execute_operator( op1, op2, c /* any of ^ * / % + - */ ) );
		}
		else
			assert( false ); // unexpected symbol...
	}
	return s.top();
}



/* TODO
 * - posfixo com numeros maiores que 9
 * - calcular posfixo com numeros maiores que 9 
 * */

/* MUDANCAS DE ESTRUTURA:
 * o espaco agora ira representar fim de numero ou fim de operador
 * */
