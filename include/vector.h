#ifndef SC_VECTOR_H 
#define SC_VECTOR_H // A include guard do STL é _STL_VECTOR_H, no entanto, é legal colocar o nome do namespace mesmo assim para nao confundir.

#include <iostream>

namespace sc {
    
    template<typename T>
    class vector;
    
    template<typename T>
    void swap(vector<T>& first_, vector<T>& second_ );
    
    template<typename T>
    std::ostream & operator<<(std::ostream & os_, const vector<T>& v_ );
    
    
    /// Implementa a infraestrutura para suportar um ponteiro bidirecional.
    template < typename T>
    class MyIterator {
        
    public:
        
        /// Alias
        /// Alias para o tipo de dado utilizado no programa.
        using value_type = T;
        /// Ponteiro para o valor do tipo.
        using pointer = value_type *;
        /// Referência para o valor do tipo.
        using reference = value_type &;
        /// Referência para o valor constante do tipo.
        using const_reference = const value_type &;  
        /// Tipo de diferência para calcular a distância entre dois ponteiros.
        using difference_type = std::ptrdiff_t;
        
        /// Construtor a partir de um ponteiro. 
        explicit MyIterator( pointer pt = nullptr );
        
        /// Construtor a partir de uma referência a outra classe MyIterator<T>.
        MyIterator( const MyIterator<T> &);
        
        /// Acessar o conteúdo o qual o ponteiro aponta.
        reference operator*( ) const;
        
        /// Destrutor da classe.
        ~MyIterator();
        
        /// Operador de pré-incremento.
        MyIterator & operator++( );
        
        /// Operador de pós-incremento.
        MyIterator operator++( int );
        
        /// Operador de pré-decremento.
        MyIterator & operator--( );
        
        /// Operador de pós-decremento.
        MyIterator operator--( int ); 
        
        /// Operador de soma.
        MyIterator operator+( int );
        
        /// Operador de subtração.
        MyIterator operator-( int );
        
        /// Sobrecarga do operador ->.
        MyIterator * operator->( void ) const;
        
        /// Operador de comparação se é <=.
        bool operator<=( const MyIterator<T> & rhs ) const;
        
        /// Operador de comparação se é >=.
        bool operator>( const MyIterator<T> & rhs ) const;
        
        /// Operador de comparação se é <
        bool operator<( const MyIterator<T> & rhs ) const;
        
        /// Operador de comparação se é >
        bool operator>=( const MyIterator<T> & rhs ) const;
        
        /// Comparar dois iteradores se são iguais.
        bool operator==( const MyIterator<T> & rhs ) const;
        
        /// Comprar dois iteradores se são difentes.
        bool operator!=( const MyIterator<T> & rhs ) const;
        
        /// Operador de atribuição.
        MyIterator & operator=( const MyIterator<T> & rhs );
        
        // Operador de diferença entre ponteiros.
        difference_type operator-( const MyIterator & rhs ) const;
        
    private:
        /// O ponteiro.
        T *current;
        
    };
    
    /// A classe vector implementa a lista TAD com array dinâmico (conhecido como vector).
    template<typename T>
    class vector {
        
    public:
        
        // [-] ALIAS
        
        using size_type = unsigned long;                                //!< The size type.
        using value_type = T;                                           //!< The value_type.
        using pointer = value_type *;                                   //!< Pointer to a value stored in the container. 
        using reference = value_type &;                                 //!< Reference to a value stored in the container. 
        using const_reference = const value_type &;                     //!< Const reference to a value stored in the container.
        using iterator = MyIterator< T >;                               //!< The iterator, instantiated from a template class. 
        using const_iterator = MyIterator< const value_type >;          //!< The const_iterator, instantiated from a template class.
        
        // [--] PUBLIC ATTRIBUTES
        
        const static size_type DEFAULT_SIZE = 1;                        //!< Size used for init and clear vector.
        
        // [I] SPECIAL MEMBERS
        
        /// Gera um vetor com a configuração padrão - tamanho 0, caso o usuário não informe o valor.
        vector( size_type size = DEFAULT_SIZE );
        /// Desconstrutor da classe vector.
        ~vector( );
        /// Construtor a partir de um outro vector.
        vector(const vector&);
        /// Construtor a partir de uma lista inicializadora.
        vector( const std::initializer_list<T> &);
        /// Construtor de movimento de um outro vector.
        vector(vector&&);
        /// Contrutor a partir de intervalos de vetores.
        template < typename InputItr >
        vector( InputItr, InputItr );          
        
        /// Operador de atribuição.
        vector & operator=( const vector & );
        /// Operador de movimento.
        vector & operator=( vector && );
        
        /// Retorna um ponteiro para o inicio da lista.
        iterator begin(void);
        /// Retorna um ponteiro para o final da lista.
        iterator end(void);
        /// Retorna um ponteiro constante para o inicio da lista.
        const_iterator cbegin(void) const;
        /// Retorna um ponteiro constante para o final da lista.
        const_iterator cend(void) const;
        
        /// Retorna a quantidade de elementos na lista.        
        size_type size( void ) const;
        /// Retorna a capacidade total da lista.
        size_type capacity( void ) const;
        /// Verifica se a lista está vazia.
        bool empty( void ) const;
        /// Verifica se a lista está cheia.
        bool full( void ) const;
        
        /// Limpa a lista.        
        void clear( void );
        /// Insere um elemento no início da lista.
        void push_front( const_reference );
        /// Insere um elemento no final da lista.
        void push_back( const_reference );
        /// Remove um elemento do final da lista.
        void pop_back( void );
        /// Remove um elemento do início da lista.
        void pop_front( void );
        /// Insere um elemento em um local específico da lista.
        iterator insert( iterator , const_reference );
        /// Insere valores de uma lista a partir de uma posição na lista original.
        template < typename InputItr >
        iterator insert( iterator , InputItr , InputItr );
        /// Insere valores a partir de uma lista inicializadora a partir de uma posição na lista original.
        iterator insert( iterator, std::initializer_list< T > );
        /// Aumenta a capacidade da lista.
        void reserve( size_type );
        /// Diminui a lista de forma que a capacidade fique igual ao tamanho.
        void shrink_to_fit( void );
        /// Atribui um número específico de cópias de um valor na lista.
        void assign( size_type count_, const_reference value_);
        /// Modifica os elementos da lista a partir de uma lista inicializadora.
        void assign( std::initializer_list<T> );
        /// Modifica os elementos de uma lista a partir de um intervalo.
        template < typename InputItr >
        void assign( InputItr, InputItr );
        /*! 
         * Remove elementos específicos da lista. 
         *
         * \note se o último ponteiro é depois do container end, o último será configurado para o método end e 
         * e o método retornará o primeiro argumento. Apagar um elemento depois do último elemento válido não é uma opção.
         */
        iterator erase( iterator, iterator );
        /*! 
         * Remove um elemento específico da lista, o qual será o qual o ponteiro informado aponta.
         *
         * \note Apagar um elemento depois do último elemento válido não é uma opção..
         */
        iterator erase( iterator );
        
        /// Acessa o último elemento da lista.
        const_reference back( void ) const;
        /// Acessa o primeiro elemento da lista.
        const_reference front( void ) const;
        /// Acessa um elemento específico da lista, retornando uma referência constante a posição informada.
        const_reference operator[]( size_type ) const;
        /// Acessa um elemento específico da lista, retornando uma referência a posição informada.
        reference operator[]( size_type );
        /// Acessa um elemento específico da lista verificando se ele está dentro do intervalo da lista, e retorna uma uma referência constante para o elemento.
        const_reference at( size_type ) const;
        /// Acessa um elemento específico da lista verificando se ele está dentro do intervalo da lista, e retorna uma uma referência constante para o elemento.
        reference at( size_type );
        pointer data( void );
        const_reference data( void ) const;
        
        
        /// Sobrecarga do operador de igualdade.      
        bool operator==( const vector & ) const;
        /// Sobrecarga do operador de desigualdade.
        bool operator!=( const vector & ) const;
        
        

        friend std::ostream & operator<< <T>(std::ostream & os_, const vector& v_ );
        
        friend void swap<T>(vector& first_, vector& second_ );
        /* nota: podemos dizer que cada /Template instantiation/ do metodo swap 
         *             será friend da /Template instantiation/ de A correnspondende usando <T>
         *             apos o nome da funcao. Exemplo: Se quisemos que o swap so funcione para
         *             inteiros, declaramos */
        
        private:
            
            size_type m_end;	        //<! Tamanho da lista (ou a quantidade até o último elemento válido).
            size_type m_capacity;	    //<! A capacidade total da lista.
            T *m_storage;		        //<! O armazenador de data para um array dinâmico.
            
    };
    
}

#include "vector.inl"

#endif
