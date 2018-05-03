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
#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error

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

/// Converts a expression in infix notation to a corresponding profix representation.
std::string infix_to_postfix( std::string );

/// Converts a char (1-digit operand) into an integer.
value_type char2integer( char c )
{ return c-'0'; }

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
        case '^': return 3;

        case '*':
        case '/':
        case '%': return 2;

        case '+':
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

    /*
    if ( get_precedence(op1) >= get_precedence(op2) )
    {
        return is_right_association( op1 ) ? false : true ;
    }
    return false;
    */
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
        //default:
    }
    throw std::runtime_error("Invalid operator!");
}

int main()
{
    // A expression is a queue of sysmbols (chars).
    std::string expression = "4/(5^2)+(6^2^3)";
    std::string expression2 = "1+ 3 * ( 4 + 8 * 3 ^7)";

    auto postfix = infix_to_postfix(expression2);
    std::cout << ">>> Input (infix)    = " << expression2 << "\n";
    std::cout << ">>> Output (postfix) = " << postfix << "\n";

    auto result = evaluate_postfix( postfix );
    std::cout << ">>> Result is: " << result << std::endl;
    std::cout << "\n>>> Normal exiting...\n";
    return EXIT_SUCCESS;
}

std::string infix_to_postfix( std::string infix )
{
    std::stack< symbol > s; // auxiliary data structure.
    std::string postfix; // stores the postfix expression

    // Process each incoming symbol
    for( const auto & c : infix )
    {
        if ( is_operand( c ) )
            postfix += c; // send it straight to the output symbol queue.
        else if ( is_opening_scope( c ) )
            s.push( c ); // always goes into the "waiting room"
        else if ( is_closing_scope( c ) )
        {
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
    std::stack< value_type > s;
    // For each operator/operando in the input postfix expression do this...
    for( const auto & c : postfix )
    {
        if ( is_operand( c ) )
            s.push( char2integer(c) ); // Do not forget to convert it into integer.
        else if ( is_operator( c ) )
        {
            // IMPORTANT: Pop out operandos in reverse order!
            auto op2 = s.top(); s.pop();
            auto op1 = s.top(); s.pop();
            // The result of the operation is pushed back into the stack.
            s.push( execute_operator( op1, op2, c /* any of ^ * / % + - */ ) );
        }
        else assert( false ); // unexpected symbol...
    }
    return s.top();
}
