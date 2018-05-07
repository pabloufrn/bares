#include "vector.h"

using namespace sc;

// MYITERATOR CLASS METHOD

template < typename T >
MyIterator<T>::MyIterator(MyIterator<T>::pointer pt){
    this->current = pt;
}

template < typename T >
MyIterator<T>::MyIterator( const MyIterator<T> &) = default;

template < typename T >
MyIterator<T>::~MyIterator() = default;

// O operator-> retorna a referencia do ponteiro atual?

template < typename T >
MyIterator<T> * MyIterator<T>::operator->( void ) const{
    return &this->current;
}

template < typename T >
MyIterator<T> & MyIterator<T>::operator=( const MyIterator<T> & rhs ){
    this->current = rhs.current;
    return *this;
}

template < typename T >
typename MyIterator<T>::reference MyIterator<T>::operator*( void ) const{
    return *this->current;
}

template < typename T >
sc::MyIterator<T> & MyIterator<T>::operator++( void ){
    ++this->current;
    return *this;
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator++( int ){
    auto temp(*this);
    ++this->current;
    return temp;
}

template < typename T >
sc::MyIterator<T> & MyIterator<T>::operator--( void ){
    --this->current;
    return *this;
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator--( int ){
    auto temp(*this);
    --this->current;
    return temp;
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator+( int value ){
    return MyIterator<T>(this->current+value); // conversão explicita
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator-( int value ){
    return MyIterator<T>(this->current-value); // conversão explicita
}

template < typename T >
bool MyIterator<T>::operator<=( const MyIterator<T> & rhs ) const {
    return this->current <= rhs.current;
}

template < typename T >
bool MyIterator<T>::operator>=( const MyIterator<T> & rhs ) const {
    return this->current >= rhs.current ;
}

template < typename T >
bool MyIterator<T>::operator<( const MyIterator<T> & rhs ) const {
    return this->current < rhs.current;
}

template < typename T >
bool MyIterator<T>::operator>( const MyIterator<T> & rhs ) const {
    return this->current > rhs.current ;
}

template < typename T >
bool sc::MyIterator<T>::operator==( const MyIterator<T> & rhs ) const {
    return this->current == rhs.current;
}

template < typename T >
bool sc::MyIterator<T>::operator!=( const MyIterator<T> & rhs ) const {
    return this->current != rhs.current;
}

template < typename T >
typename MyIterator<T>::difference_type MyIterator<T>::operator-( const MyIterator<T> & rhs ) const{
    return MyIterator<T>::difference_type(this->current - rhs.current);
}

// -------------------- VECTOR CLASS ---------------------------


// [I] SPECIAL MEMBERS


template< typename T>
vector<T>::vector( size_type size ) {
    this->m_end = 0;
    this->m_capacity = size;
    this->m_storage = new T[size];
}

template < typename T >
sc::vector<T>::~vector( ) {
    delete [] m_storage;
}


template < typename T >
vector<T>::vector(const vector<T>& vtr)
{
    this->m_capacity = vtr.m_capacity;
    this->m_storage = new T[this->m_capacity];
    this->m_end = vtr.m_end;
    
    auto f(this->begin());
    int i = 0;
    while((f+i) != this->end()){
        *(f+i) = *(vtr.m_storage+i);
        i++;
    }
    
}

template < typename T >
vector<T>::vector(vector<T>&& vtr){
    this->m_capacity = vtr.m_capacity;
    this->m_end = vtr.m_end;
    this->m_storage = std::move(vtr.m_storage);
    
    vtr.m_storage = new T[DEFAULT_SIZE];
    vtr.m_capacity = DEFAULT_SIZE;
    vtr.m_end = 0;
}

template < typename T >
vector<T>::vector( const std::initializer_list<T> & rhf ){
    this->m_capacity = rhf.size()+1;
    this->m_storage = new T[m_capacity];
    std::copy( rhf.begin(), rhf.end(), &m_storage[0]);
    
    
    this->m_end = rhf.size();
}

template<class T>
template < typename InputItr >
vector<T>::vector( InputItr first, InputItr last){
    this->m_capacity = last - first;
    this->m_storage = new T[this->m_capacity];
    this->m_end = this->m_capacity;
    for(auto i(0u); i < this->m_end; ++i){
        this->m_storage[i] = *(first+i); 
    }
}

template < typename T >
vector<T> & vector<T>::operator=( const vector<T> & vtr ) {
    this->m_end = vtr.m_end;
    this->m_capacity = vtr.m_capacity;
    
    delete [] this->m_storage;
    this->m_storage = new T[vtr.m_capacity];
    
    for( auto i(0u); i < vtr.m_end; i++ )
        this->m_storage[i] = vtr.m_storage[i];
    
    return *this;
}


template < typename T >
vector<T> & vector<T>::operator=( vector<T> && vtr ){
    this->m_capacity = vtr.m_capacity;
    this->m_end = vtr.m_end;
    
    delete [] this->m_storage;
    
    this->m_storage = std::move(vtr.m_storage);
    vtr.m_storage = new T[DEFAULT_SIZE];
    vtr.m_capacity = DEFAULT_SIZE;
    vtr.m_end = 0;
    
    return *this;
}

// [II] ITERATORS

template < typename T >
typename vector<T>::iterator vector<T>::begin(void) {
    return vector<T>::iterator(this->m_storage);
}

template < typename T >
typename vector<T>::iterator vector<T>::end(void) {
    return vector<T>::iterator(this->m_storage + this->m_end );
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cbegin(void) const {
    return vector<T>::const_iterator ( this->m_storage );
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cend(void) const {
    return vector<T>::const_iterator( this->m_storage  + this->m_end);
}


// [III] Capacity


template < typename T >
typename vector<T>::size_type vector<T>::size( void ) const {
    return this->m_end;
}

template < typename T >
typename vector<T>::size_type vector<T>::capacity( void ) const {
    return this->m_capacity;
}

template < typename T >
bool vector<T>::empty( void ) const {
    return this->m_end == 0;
}


// [IV] Modifiers


template < typename T >
void vector<T>::clear( void ){
    delete [] this->m_storage;
    this->m_storage = new T[DEFAULT_SIZE];
    this->m_capacity = DEFAULT_SIZE;
    this->m_end = 0;
}

template < typename T >
void vector<T>::push_front( vector<T>::const_reference value ){
    if(this->m_end == this->m_capacity)
        this->reserve( this->m_capacity * 2 );
    
    for( auto i(this->m_end) ; i > 0 ; --i ){
        std::swap(*(this->m_storage+i-1), *(this->m_storage+i));
    }
    this->m_storage[0] = value;
    m_end++;
    
}

template < typename T >
void vector<T>::push_back( vector<T>::const_reference value ){
    if(this->m_end == this->m_capacity)
        this->reserve(this->m_capacity * 2);
    this->m_storage[this->m_end++] = value;
}

template < typename T >
void vector<T>::pop_back( void ){
    if(this->empty())
        return;
    --this->m_end;
}

template < typename T >
void vector<T>::pop_front( void ){
    if(this->empty())
        return;
    for( auto i(0u) ; i < this->m_end-1; ++i )
        std::swap(this->m_storage[i], this->m_storage[i+1]);
    --this->m_end;
}

template < typename T >
typename vector<T>::iterator vector<T>::insert( iterator pos_ , const_reference value_ ){
    //m_end++;
    iterator i (m_storage);
    int pos_posicao = pos_-i;

    if(m_end+1 >= this->m_capacity)
        this->reserve((this->m_capacity) * 2);

    iterator new_i (m_storage);

    auto last_ = new_i + m_end;

    pos_ = new_i+pos_posicao;

    while( last_  >= pos_ ){
        T temp = *(last_);
        *(last_+1) = temp;
        --last_;
    }
    
    *pos_ = value_;   
    m_end = m_end + 1;


    return iterator(pos_);
}

template < typename T >
template < typename InputItr >
typename vector<T>::iterator vector<T>::insert( iterator pos_ , InputItr first_ , InputItr last_ ){
    
    int qnt_new = last_ - first_;
    if( qnt_new == 0 )
        return pos_;

    iterator a (m_storage);
    int apartir( pos_ - a );
    int ate(apartir + qnt_new);

    if(m_end+qnt_new >= this->m_capacity)
        this->reserve(this->m_capacity * 2);

    iterator a_n (m_storage);

    int endtotal = m_end+qnt_new;
    auto las(a_n+endtotal);

    while(las >= (a_n+ate)){
        *(las) = *(las-qnt_new);
        las--;
    }
    
    m_end += qnt_new;
    
    int i = 0;
    while(first_ < last_){
        *(a_n+apartir+i) = *first_;
        first_++;
        i++;
    }

    return pos_;
    
}

template < typename T >
typename vector<T>::iterator vector<T>::insert( iterator pos_, std::initializer_list< T > ilist_ ){

    if( ilist_.size() == 0 )
        return pos_;

    iterator a (m_storage);
    int apartir( pos_ - a );
    int dif = ilist_.end() - ilist_.begin();
    int ate(apartir + dif);

    if(m_end >= this->m_capacity)
        this->reserve(this->m_capacity * 2);

    iterator a_n (m_storage);


    int endtotal = m_end+dif;
    auto las(a_n+endtotal);

    while(las >= (a_n+ate)){
        *(las) = *(las-dif);
        las--;
    }
    
    m_end += dif;
    
    std::copy( ilist_.begin(), ilist_.end(), &(*(a_n+apartir))); // sem conversao implicita de iterator para ponteiro
    
    return a_n+apartir;
    
}

template < typename T >
void vector<T>::reserve(vector<T>::size_type size)
{
    if(size <= this->m_capacity)
        return;
    T* new_storage = new T[size];
    this->m_capacity = size;
    auto end(this->m_end);
    for(auto i(0u); i < end; ++i) {
        new_storage[i] = this->m_storage[i]; 
    }
    delete [] this->m_storage;
    this->m_storage = new_storage;
}

template < typename T >
void vector<T>::shrink_to_fit( void )
{
    typename vector<T>::ponter new_storage = new vector<T>::value_type[this->m_end];
    for(auto i(0u); i < this->m_end; ++i){
        new_storage[i] = this->m_storage[i];
    }
    delete [] this->m_storage;
    this->m_storage = new_storage;
    this->capacity = this->m_end;
}

template < typename T >
void vector<T>::assign( vector<T>::size_type count_, vector<T>::const_reference value_ )
{    
    delete [] this->m_storage;
    m_storage = new T[count_+1];
    for(auto i(0u); i < count_; i++){
        m_storage[i] = value_;
    }
    m_end = count_;
    m_capacity = count_+1;
}

template < typename T >
void vector<T>::assign( std::initializer_list<T> il ){
    if(il.size() > this->m_capacity)
        this->reserve(il.size() * 2);
    
    std::copy( il.begin(), il.end(), &m_storage[0]);
    m_end = il.size();
}

template < typename T >
template < typename InputItr >
void vector<T>::assign( InputItr first, InputItr last){
    vector<T>::size_type size = last - first;
    iterator f(first);
    if(size > this->m_capacity)
        this->reserve(size * 2);
    
    for(auto i(0u); i < size; ++i)
        this->m_storage[i] = *(f+i);
    
    this->m_end = size;
}

template < typename T >
typename vector<T>::iterator vector<T>::erase( vector<T>::iterator first, vector<T>::iterator last){
    if(last > vector<T>::iterator ( this->m_storage + this->m_end ))                    
        last = vector<T>::iterator ( this->m_storage + this->m_end );          
    vector<T>::iterator old_first = first;
    vector<T>::iterator aux = last; 
    vector<T>::iterator p_m_end = vector<T>::iterator(this->m_storage + this->m_end);
    while(aux < p_m_end)
        *(first++) = *(aux++);
    
    this->m_end -= last - old_first;
    return old_first;
}


template < typename T >
typename vector<T>::iterator vector<T>::erase( vector<T>::iterator pos){
    auto p_m_end = vector<T>::iterator ( this->m_storage + this->m_end );
    if(pos >= vector<T>::iterator ( p_m_end ))
        return vector<T>::iterator( p_m_end );
    
    auto old_pos = pos;
    auto aux = pos+1;
    
    while(aux < p_m_end)
        *(pos++) = *(aux++);
    this->m_end--;
    return old_pos;
}


// [V] Element access


template < typename T >
typename vector<T>::const_reference vector<T>::back( void ) const {
    return const_cast< vector<T>::const_reference > ( this->m_storage[this->m_end-1] );
}

template < typename T >
typename vector<T>::const_reference vector<T>::front( void ) const {
    return const_cast< vector<T>::const_reference > ( * this->m_storage );
}

template < typename T >
typename vector<T>::const_reference vector<T>::operator[]( size_type pos ) const {
    return const_cast< vector<T>::const_reference > ( this->m_storage [pos] );
}

template < typename T >
typename vector<T>::reference vector<T>::operator[]( size_type pos ) {
    return this->m_storage[pos];
}

template < typename T >
typename vector<T>::const_reference vector<T>::at( vector<T>::size_type pos ) const
{
    if(pos >= this->m_end || pos < 0)
        throw std::out_of_range("Index provided is outside the array range.");
    return this->m_storage[pos];
}

template < typename T >
typename vector<T>::reference vector<T>::at( vector<T>::size_type pos )
{
    if(pos >= this->m_end || pos < 0)
        throw std::out_of_range("Index provided is outside the array range.");
    return this->m_storage[pos];
}


template < typename T >
typename vector<T>::pointer vector<T>::data( void ) {
    return this->m_storage;
}

template < typename T >
typename vector<T>::const_reference vector<T>::data( void ) const
{
    return const_cast< vector<T>::const_reference > ( * this->m_storage );
}


// [VI] Operators


template < typename T >
bool vector<T>::operator==( const vector<T> & vtr) const{
    if( this->m_end == vtr.m_end && this->m_capacity == vtr.m_capacity ){
        for( auto i(0u) ; i < this->m_capacity ; i++ ){
            if(*(this->m_storage+i) != *(vtr.m_storage+i))
                return false;
        }
        return true;
    }
    
    return false;
}

template < typename T >
bool vector<T>::operator!=( const vector & vtr) const{
    if( this->m_end == vtr.m_end && this->m_capacity == vtr.m_capacity ){
        for( auto i(0u) ; i < this->m_capacity ; i++ ){
            if(*(this->m_storage+i) == *(vtr.m_storage+i)){
                return false;
        }
        return true;
    }
    
    return true;
    }  
}


// [VII] Friend functions.

template < typename T >
std::ostream & sc::operator<<( std::ostream& os_, const vector<T>& v_ ){
    os_ << "Vetor = [ ";
    for( auto i(0u); i < v_.m_end ; i++ ){
        os_ << *(v_.m_storage+i) << " ";
    }
    os_ << "]";
    
    return os_;
}

template < typename T >
void sc::swap(vector<T>& first_, vector<T>& second_ ){
    vector<T> tmp(std::move(first_));           // | Move o container first_ para o tmp
    first_ = std::move(second_);                // | Move o container second_ para o first_
    second_ = std::move(tmp);                   // | Move o container tmp para o second_
}

// [+] Non-member functions

template < typename T >
bool operator==( vector<T>& lhs, vector<T>& rhs ){
    if( lhs.m_end == rhs.m_end && lhs.m_capacity == rhs.m_capacity ){
        for( auto i(0u) ; i < lhs.m_capacity ; i++ ){
            if(*(lhs.m_storage+i) != *(rhs.m_storage+i))
                return false;
        }
        return true;
    }
    
    return false;
}

template < typename T >
bool operator!=( const vector<T>& lhs, const vector<T>& rhs ){
    if( lhs.m_end == rhs.m_end && lhs.m_capacity == rhs.m_capacity ){
        for( auto i(0u) ; i < lhs.m_capacity ; i++ ){
            if(*(lhs.m_storage+i) != *(rhs.m_storage+i))
                return true;
        }
        return false;
    }
    
    return true;
}

template < typename T >
bool sc::vector<T>::full( void ) const{
    if( this->m_size >= this->m_capacity ){
        return true;
    } else{
        return false;
    }
}
