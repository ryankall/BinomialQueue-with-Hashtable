/* 
 * File:   BinQueuePlusPlus.h
 * Author: Ryan Kallicharran
 * Description: BinQueuePlusPlus that uses hash table and 
 *              binomial queue together
 * Created on November 9, 2015, 12:52 PM
 */



#ifndef BINQUEUEPLUSPLUS_H
#define	BINQUEUEPLUSPLUS_H

#include "BinomialQueue.h"
#include "QuadraticProbing.h"
#include <fstream>
#include <string>



class BinQueuePlusPlus  {
public:
    
    //Default constructor
    BinQueuePlusPlus();
    //Destructor
    ~BinQueuePlusPlus();
    
    /**
     * Empties the queue and hash table
     */
    void makeEmpty();
    
    /**
     * Build the queue and hash table items from word file
     * @return 
     */
    bool readFile();
    
    /**
     * Get the comparison counter from queue
     * @return comparison counter
     */
    int getComparCount();
    
    /**
     * Get the assignment counter from queue
     * @return assignment counter
     */
    int getAssignCount();
    
    /**
     * Deletes the min string from queue and hash table
     * @return the item that was deleted
     */
    string deleteMin();
    
    /**
     * Checks if the string exist in hash table only ( O(1) look up)
     * @param key
     * @return true if it exist in table; otherwise false
     */
    bool contains(string & key);
    
    /**
     * Removes a given word from the queue and hash table
     * @param key
     * @return true if remove was successful
     */
    bool remove(string & key);

private:
    
    string HashedObj;//hold our word
    
    
    BinomialNode<string> * Pointer;//holds our point
    HashTable< string , BinomialNode<string> > table; //hash table that hold pair of object and pointer
    BinomialQueue< string > bQueue; //our queue
    
    /**
     * Finds a given key  in the hash table 
     * @param key string
     * @return BinomialNode pointer of the key
     */
    BinomialNode<string>* find(  string & key );
    
    /**
     * Inserts a given a key in the queue and hash table
     * @param key string
     */
    void insert( string  & key);
    
    /**
     * Decrease a given key Node  and percolate them up in the queue
     * @param keyNode
     * @param key
     * @return true if key was move to from of the queue
     */
    bool decreaseKey( BinomialNode<string>* keyNode, string  key);

  
};
#include "BinQueuePlusPlus.cpp"
#endif	/* BINQUEUEPLUSPLUS_H */

