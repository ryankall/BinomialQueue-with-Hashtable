/**
 * Definition of functions for QuadraticProbing.h
 */

#include "QuadraticProbing.h"

using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
template <typename HashedObj, typename OtherObj>
bool HashTable< HashedObj, OtherObj> ::isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
template <typename HashedObj, typename OtherObj>
int HashTable< HashedObj, OtherObj> ::nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}


template <typename HashedObj, typename OtherObj>
HashTable<HashedObj, OtherObj>::HashTable( int size ) : array( nextPrime( size ) )
      { makeEmpty( ); }

template <typename HashedObj, typename OtherObj>
bool HashTable<HashedObj, OtherObj>::contains( const HashedObj & x ) const
{
    return isActive( findPos( x ) );
}

template <typename HashedObj, typename OtherObj>
void HashTable<HashedObj, OtherObj>::makeEmpty( )
{
    //reset  current size
    currentSize = 0;
    //change state of all item in array
    for( auto & entry : array )
        entry.info = EMPTY;
}

template<typename HashedObj, typename OtherObj>
bool HashTable<HashedObj, OtherObj>::insert(  HashedObj & x, OtherObj *p )
{
    // Insert x as active
    int currentPos = findPos( x );
    
    //check if x is in the table
    if( isActive( currentPos ) )
        return false;
    
    //set state of  x
    array[ currentPos ].element = x;
    array[ currentPos ].pointer = p;    
    array[ currentPos ].info = ACTIVE;

    //check if the  current size of array is greater than half 
    //then rehash if it is
    if( ++currentSize > array.size( ) / 2 )
        rehash( );

    return true;
}

template <typename HashedObj, typename OtherObj>
bool HashTable<HashedObj, OtherObj>::insert( HashedObj && x, OtherObj && p )
{
    // Insert x as active
    int currentPos = findPos( x );
    
    //check if x  in the table
    if( isActive( currentPos ) )
        return false;

    //set state of x 
    array[ currentPos ].element = std::move( x );
    array[ currentPos ].pointer = std::move ( p );
    array[ currentPos ].info = ACTIVE;

    //check if the  current size of array is greater than half 
    //then rehash if it is
    if( ++currentSize > array.size( ) / 2 )
        rehash( );

    return true;
}

template <typename HashedObj, typename OtherObj>
bool HashTable<HashedObj, OtherObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    //check if key in the table
    if( !isActive( currentPos ) )
        return false;

    //set state to deleted
    array[ currentPos ].info = DELETED;
    return true;
}

template <typename HashedObj, typename OtherObj>
OtherObj* HashTable<HashedObj, OtherObj>:: find( HashedObj &key){
    
    int currentPos = findPos( key );
    //check if the key exist in table
    if( !isActive( currentPos ) )
        return nullptr;
    
    return array [ currentPos ].pointer; 
    
}

template <typename HashedObj, typename OtherObj>
void HashTable<HashedObj, OtherObj>:: update( HashedObj& key, OtherObj* newPointer ){
    //finds position
    int currentPos = findPos( key );
    //set pointers
    array [ currentPos ].pointer = newPointer;
}

//////////////////////////////////////////////////////////////////////////////
//                         Protected Function                               //
//////////////////////////////////////////////////////////////////////////////



template <typename HashedObj, typename OtherObj>
bool HashTable<HashedObj, OtherObj>::isActive( int currentPos ) const
  { return array[ currentPos ].info == ACTIVE; }

template <typename HashedObj, typename OtherObj>
int HashTable<HashedObj, OtherObj>::findPos( const HashedObj & x ) const
{
    int offset = 1;
    //hash x to a get a integer for the table
    unsigned int currentPos = myhash( x );

    //check if array position is not empty is not the same item 
    //otherwise this does not 
    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        currentPos += offset;  // Compute ith probe
        offset += 2;
        if( currentPos >= array.size( ) )
            currentPos -= array.size( );
    }

    return currentPos;
}

template <typename HashedObj, typename OtherObj>
void HashTable<HashedObj, OtherObj>::rehash( )
{
    vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for( auto & entry : array )
        entry.info = EMPTY;

        // Copy table over
    currentSize = 0;
    for( auto & entry : oldArray )
        if( entry.info == ACTIVE )
            insert(  entry.element , entry.pointer );
}

template <typename HashedObj, typename OtherObj>
size_t HashTable<HashedObj, OtherObj>::myhash( const HashedObj & x ) const
{
    //hash function
    static hash <HashedObj> hf;
    return hf( x ) % array.size( );
}
