#ifndef SC_STACK 
#define SC_STACK

#include <iostream>
#include <stdexcept>

namespace pl{

	template < typename T >
	class stack{
		using size_type 	= 	unsigned long;
		using value_type 	= 	T;
		using reference 	= 	T&;
		using const_reference 	= const T&;
		using pointer 		= 	T*;

	private:
		pointer m_storage;	// armazenamento
		size_t m_end;			// quantidade de elementos
		size_t m_capacity;		// capacidade total


	public:

		stack( void ){
			m_storage = new T[1];
			m_capacity = 1;
			m_end = 0;
		}

		~stack(){
			delete [] m_storage;
		}

		void push(  const_reference vl_ ){	
			if( full() == true ){
				pointer new_storage = new T[m_capacity*2];
				for( auto i(0u) ; i < m_end; i++){
					*(new_storage+i) = *(m_storage+i);
				}
				m_capacity *= 2;
				delete [] this->m_storage;
				m_storage = new_storage;
			}

			m_storage[m_end] = vl_;
			++m_end;
		}

		void pop( void ){
			if(empty() == true)
				throw std::runtime_error("[stack::pop()] A pilha está vázia.");
			
			--this->m_end;
		}

		value_type top( void ) const{
			if(empty() == true)
				throw std::runtime_error("[stack::top()] A pilha está vázia.");
			return *(m_storage+m_end-1);
		}

		void clear( void ){
			//delete [] this->m_storage;
			m_end = 0;
		}

		bool empty( void ) const{
			return this->m_end == 0;
		}	

		int size( void ) const{
			return m_end;
		}

		bool full( void ) const{
			return m_end >= m_capacity;
		}

		stack& operator=( const stack st ){
			this->m_end = st.m_end;
			this->m_capacity = st.m_capacity;
			m_storage = new T[m_capacity];

			auto i(0u);
			while(i != m_end){
				*(m_storage+i) = *(st.m_storage+i);
				++i;
			}

			return *this;
		}
	};
}

#endif