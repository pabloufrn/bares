#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>   // std::string
#include <iostream> // std::ostream

/// Representação de um token.
struct Token
{
    public:
        enum class token_t : int
        {
            OPERAND = 0,        //!< Tipo de representação numerica.
            OPERATOR,           //!< Tipo de representação de "+", "-", "*", "/", "%", "^".
            PARENTHESIS_OPEN,         //!< Representação do "(".
            PARENTHESIS_CLOSE         //!< Representação do ")".
        };
        
        std::string value; //!< O valor de um token como string.
        token_t type;      //!< O tipode token que pode ser token_t::OPERAND, token_t::OPERATOR, token_t::PARENTHESIS_OPEN ou token_t::PARENTHESIS_CLOSE.
        
        /// Contrutor default.
        explicit Token( std::string value_="", token_t type_ = token_t::OPERAND )
        : value( value_ )
        , type( type_ )
        {/* vazio */}
        
        /// Ajudar no debug.
        friend std::ostream & operator<<( std::ostream& os_, const Token & t_ )
        {
            std::string types[] = { "OPERAND", "OPERATOR", "PARENTHESIS_OPEN", "PARENTHESIS_CLOSE" };
            
            os_ << "<" << t_.value << "," << types[(int)(t_.type)] << ">";
            
            return os_;
        }
};

#endif
