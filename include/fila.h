#ifndef SC_QUEUE
#define SC_QUEUE

#include <iostream>
#include <stdexcept>

namespace st{

	template < typename T >
	class queue{
		using size_type 	= unsigned long;
		using value_type 	= T;
		using reference 	= T&;
		using pointer 		= T*;

	private:
		pointer m_storage;			//!< container que armazena os dados.
		size_t m_end;				//!< quantidade lógica ( ocupada ) dos dados.
		size_t m_capacity;			//!< quantidade física ( total ).

	public:
		queue( void ){
			m_storage = new T[1];
			m_end = 0;
			m_capacity = 0;
		}

		/// insere um elemento na retaguarda da fila.
		void enqueue( const reference v ){

			if( m_end == m_capacity ){
				pointer new_space = new T[m_capacity*2];

				for( auto i(0u) ; i < m_end ; ++i ){
					*(new_space+i) = *(m_storage+i);
				}

				m_capacity *= 2;
				delete [] new_space;
				m_storage = new_space;
			}

			m_storage[m_end] = v;
			++m_end;
		}

		/// remove o elemento da frente da fila.
		void dequeue( void ){

			if( m_end == 0 )
				throw std::runtime_error("[queue::dequeue()] A fila está vázia.");

			for( auto i (1u) ; i < m_end ; ++i ){
				*(m_storage+i-1) = *(m_storage+i);
			}
			--m_end;

		}
		
		/// retorna, sem remover, o elemento da frente da fila.
		value_type front( void ){

			return *m_storage;

		}
		
		/// retorna, sem remover, o elemento da retaguarda da fila.
		value_type back( void )
		{
			return *(m_storage+m_end-1);
		}

		value_type size(){
			return m_end;
		}

	};
	
}

#endif