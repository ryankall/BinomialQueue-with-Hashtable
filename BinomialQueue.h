#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include "dsexceptions.h"
#include "BinomialNode.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
  public:
    BinomialQueue( );//DEFAULT CONSTRUCTOR
    
    //CONSTRUCTOR with one one item pass at initialization
    BinomialQueue( const Comparable & item );
    /**
     * Copy constructor 
     * @param BnomialQueue
     */ 
    BinomialQueue( const BinomialQueue & rhs );
    
    /**
     * Copy constructor  (move)
     * @param BnomialQueue
     */ 
    BinomialQueue( BinomialQueue && rhs );

    //Destructor
    ~BinomialQueue( );

    
    /**
     * Deep copy.
     * @param BinomialQueue
     */
    BinomialQueue & operator=( const BinomialQueue & rhs );
        
    /**
     * Move. Deep copy
     * @param BinomialQueue
     */
    BinomialQueue & operator=( BinomialQueue && rhs );
    
    /**
     * Check if the Queue is empty
     * @return true if empty; false otherwise. 
     */
    bool isEmpty( ) const;

    /**
     * Finds the min item in the queue
     * @Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const;
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     * @param Comparable item
     * @return BinomialNode pointer of item just inserted
     */
    BinomialNode<Comparable>* insert( const Comparable & x );

    /**
     * Insert item x into the priority queue; allows duplicates.
     * @param Comparable item
     * @return BinomialNode pointer of item just inserted
     */
    BinomialNode<Comparable>* insert( Comparable && x );
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( );

    /**
     * Remove the minimum item and place it in minItem.
     * @param Comparable of minItem in queue
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem );

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( );

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * @param BinomialQueue to be merged
     */
    void merge( BinomialQueue & rhs );

    
    /**
     * Gets the comparison counter
     * @return comparison counter
     */
    int getComparCount();
    
    /**
     * Gets the assignment counter
     * @return assignmentCounter
     */
    int getAssignCount();
    
  private:
    
    int comparisonCounter; //counter for comparison
    int assignmentCounter; //counter for assignment
    BinomialNode<Comparable> * pointer;

    const static int DEFAULT_TREES = 1;
    
    
    vector<BinomialNode<Comparable> *> theTrees;  // An array of tree roots
    unsigned currentSize;                  // Number of items in the priority queue
    
    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * @return the index of tree containing the smallest item.
     */
    unsigned int findMinIndex( ) const;

    /**
     * Get the capacity of the queue
     * @return the capacity.
     */
    unsigned int capacity( ) const;

    /**
     * combines two trees
     * @param BinomialNode pointer to be combined 
     * @param BinomialNode pointer to be combined
     * @return the result of merging equal-sized t1 and t2.
     */
    BinomialNode<Comparable> * combineTrees( BinomialNode<Comparable> *t1, BinomialNode<Comparable> *t2 );

    /**
     * Make a binomial tree logically empty, and free memory.
     * @param BinomialNode pointer address of a tree root
     */
    void makeEmpty( BinomialNode<Comparable> * & t );

    /**
     * Internal method to clone subtree.
     * @param BinomialNode pointer to be clone
     * @return BinomialNode pointer of the cloned tree
     */
    BinomialNode<Comparable>* clone( BinomialNode<Comparable> * t ) const;
};
#include "BinomialQueue.cpp"
#endif
