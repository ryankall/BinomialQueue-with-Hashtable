#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj, typename OtherObj>
class HashTable
{
  public:
    //Constructor  
    explicit HashTable( int size=101 );
    
    /**
     * Check if a give item is in the hash table
     * @param x will be searched for
     * @return returns true if xi s found; otherwise false
     */
    bool contains( const HashedObj & x ) const;

    /**
     * Delete everything from the hash table
     */
    void makeEmpty( );

    /**
     * Insert a given item into the hash table and a given pointer
     * @param x will be inserted and kept as key
     * @param p pointer goes along with x
     * @return true if insertion completed; otherwise false
     */   
    bool insert(  HashedObj & x, OtherObj *p );
  
    /**
     * Insert a given item into the hash table and a given pointer (moving)
     * @param x will be inserted and kept as key
     * @param p pointer goes along with x
     * @return true if insertion completed; otherwise false
     */  
    bool insert( HashedObj && x, OtherObj && p );

    /**
     * Remove a given item from a hash table
     * @param x will be searched and deleted from table
     * @return true if x if found and removed; otherwise false
     */
    bool remove( const HashedObj & x); 
    
    /**
     * Search a given key and then remove that key from the hash table 
     * @param key that is search for
     * @return pointer that is connected to key's node; otherwise return nullptr
     */
    OtherObj* find( HashedObj &key);

    /**
     * State of Entries in the Hash table
     */
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
    /**
     * Finds the next prime number of a given prime number
     * @param n is prime number
     * @return  the next prime number
     */
    int nextPrime( int n );
    
    /**
     * Checks if a given number is prime
     * @param n a number
     * @return true if prime; otherwise false
     */
    bool isPrime( int n);
    
    /**
     * Update a given pointer in the hash by using the key to search for the position
     * @param key that will be searched
     * @param newPointer that will be set
     */
    void update( HashedObj& key, OtherObj* newPointer );
    

  private:
    struct HashEntry
    {
        HashedObj element;
        OtherObj * pointer;
        EntryType info;
        
        
        //constructor
        HashEntry( const HashedObj & e = HashedObj{ }, OtherObj* p = nullptr, EntryType i = EMPTY )
          : element{ e }, pointer{ p }, info{ i } { }
        //move constructor
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    //holds our entries
    vector<HashEntry> array;
    //holds the size of vector
    unsigned int currentSize;

    /**
     * Check if the give key is in the hash table
     * @param currentPos  in the array
     * @return true if the item is found and active;otherwise false
     */
    bool isActive( int currentPos ) const;

    /**
     * Finds a given key position in the hash table array
     * @param x the key
     * @return position of x
     */
    int findPos( const HashedObj & x ) const;

    /**
     * Create a bigger array if and re insert all entries
     */
    void rehash( );

    /**
     * Hash function for keys
     * @param x 
     * @return the number as result of the function
     */
    size_t myhash( const HashedObj & x ) const;
};

#include "QuadraticProbing.cpp"
#endif
