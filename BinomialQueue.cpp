/* 
 * File:   BinomialQueue.cpp
 * Author: Ryan Kallicharran
 * 
 * Created on November 8, 2015, 5:24 PM
 */



#include "BinomialQueue.h"


    template <typename Comparable>
    BinomialQueue<Comparable>::BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
            root = nullptr;
        currentSize = 0;
    }

    template <typename Comparable>
    BinomialQueue<Comparable>::BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
      { pointer = theTrees[ 0 ] = new BinomialNode<Comparable>{ item, nullptr, nullptr, nullptr }; }

    template <typename Comparable>
    BinomialQueue<Comparable>::BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    { 
        for( unsigned int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    template <typename Comparable>
    BinomialQueue<Comparable>::BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    { 
    }

    template <typename Comparable>
    BinomialQueue<Comparable>::~BinomialQueue( )
      { makeEmpty( ); }

    
    /**
     * Deep copy.
     */
    template <typename Comparable>
    BinomialQueue<Comparable>& BinomialQueue<Comparable>::operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    template <typename Comparable>
    BinomialQueue<Comparable> & BinomialQueue<Comparable>:: operator=( BinomialQueue && rhs )
    {   //moves
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }
    
    /**
     * Return true if empty; false otherwise.
     */
    template <typename Comparable>
    bool BinomialQueue<Comparable>::isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable & BinomialQueue<Comparable>::findMin( ) const
    {
        //throw exception if queue is empty
        if( isEmpty( ) )
            throw UnderflowException{ };

        return theTrees[ findMinIndex( ) ]->element;
    }
    
    
    //return the comparison counter 
    template <typename Comparable>
    int BinomialQueue<Comparable>::getComparCount()
    {
        return comparisonCounter;
    }
    
    //return the comparison counter 
    template <typename Comparable>
    int BinomialQueue<Comparable>::getAssignCount()
    {
        return assignmentCounter;
    }
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    template <typename Comparable>
    BinomialNode<Comparable>* BinomialQueue<Comparable>::insert( const Comparable & x )
      { 
        
        BinomialQueue<Comparable> oneItem{ x };
        assignmentCounter+=3; //from constructor
        //save the pointer to the node for return
        BinomialNode<Comparable>* ptrHolder = oneItem.pointer;
        assignmentCounter++;
        merge( oneItem );
        
        return ptrHolder;
    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    template <typename Comparable>
    BinomialNode<Comparable>* BinomialQueue<Comparable>::insert( Comparable && x )
      { 
        BinomialQueue<Comparable> oneItem{ std::move( x ) }; 
        assignmentCounter+=3; //from constructor
        //save the pointer to the node for return
        BinomialNode<Comparable>* ptrHolder = oneItem.pointer;
        assignmentCounter++;
        merge( oneItem ); 
    
        return ptrHolder;
    }
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    template <typename Comparable>
    void BinomialQueue<Comparable>::deleteMin( )
    {
        Comparable x;
        deleteMin( x );
    }

    
    
    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    template <typename Comparable>
    void BinomialQueue<Comparable>::deleteMin( Comparable & minItem )
    {
        //check if queue is empty then throw exception
        if( isEmpty( ) )
            throw UnderflowException{ };

        //find the min item    
        unsigned int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;
        
        //save child of node to be deleted
        BinomialNode<Comparable> *oldRoot = theTrees[ minIndex ];
        BinomialNode<Comparable> *deletedTree = oldRoot->leftChild;
        delete oldRoot;//delete node

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex + 1 );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    /**
     * Make the priority queue logically empty.
     */
    template <typename Comparable>
    void BinomialQueue<Comparable>:: makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     */
    template <typename Comparable>
    void BinomialQueue<Comparable>::merge( BinomialQueue & rhs )
    {
        if( this == &rhs ){    // Avoid aliasing problems
            comparisonCounter++;
            return;
        }
        currentSize += rhs.currentSize;
        assignmentCounter++;

        if( currentSize > capacity( ) )
        {   comparisonCounter++; //from if statement
            unsigned int oldNumTrees = theTrees.size( );
            assignmentCounter++;
            unsigned int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            assignmentCounter++;
            comparisonCounter++;//from max
            theTrees.resize( newNumTrees );
            assignmentCounter++;//from resize
            
            assignmentCounter++;//from initial loop
            for( unsigned int i = oldNumTrees; i < newNumTrees; ++i ){
                comparisonCounter++;
                theTrees[ i ] = nullptr;//ignore assignment for nullptr
                assignmentCounter++;//for updating i
            }
            
        }

        
        BinomialNode<Comparable> *carry = nullptr;//ignore assignment for nullptr
        assignmentCounter+=2;//initial value of loop
        for(unsigned int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            comparisonCounter++;//for loop
            assignmentCounter+=2;//for i and j
            
            BinomialNode<Comparable> *t1 = theTrees[ i ];
            assignmentCounter++;//above assignment
            BinomialNode<Comparable> *t2;
            
            if(i < rhs.theTrees.size( )){
                t2 = rhs.theTrees[ i ];  
                assignmentCounter++;//above assignment
            }else
                t2 = nullptr;
            
            //deciding which case
            comparisonCounter++; //above assignment and comparison
            int whichCase = t1 == nullptr ? 0 : 1;
            comparisonCounter++;assignmentCounter++;//above assignment and comparison
            whichCase += t2 == nullptr ? 0 : 2;
            comparisonCounter++; assignmentCounter++;//above assignment and comparison
            whichCase += carry == nullptr ? 0 : 4;
            comparisonCounter++; assignmentCounter++;//above assignment and comparison
           

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
                assignmentCounter++;//above assignment 
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
                assignmentCounter++;//above assignment
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                assignmentCounter+=2;//above assignment
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
                assignmentCounter++;//above assignment
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
                assignmentCounter++;//above assignment
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
                assignmentCounter+=2;//above assignment
                break;
            }
        }

        comparisonCounter++;//loop intial assignment
        for( auto & root : rhs.theTrees ){
            comparisonCounter++;//from loop
            assignmentCounter++;//from loop
            
            root = nullptr;//ignore assignment
            
        }
        rhs.currentSize = 0;
        comparisonCounter++;
    }    

   
    
    
//////////////////////////////////////////////////////////////////////////////
//                         Protected Function                               //
//////////////////////////////////////////////////////////////////////////////

    
    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    template <typename Comparable>
    unsigned int BinomialQueue<Comparable>::findMinIndex( ) const
    {
        unsigned int i;
        unsigned int minIndex;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }

    /**
     * Return the capacity.
     */
    template <typename Comparable>
    unsigned int BinomialQueue<Comparable>::capacity( ) const
      { return ( 1 << theTrees.size( ) ) - 1; }

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    template <typename Comparable>
    BinomialNode<Comparable> * BinomialQueue<Comparable>::combineTrees( BinomialNode<Comparable> *t1, BinomialNode<Comparable> *t2 )
    {
        if( t2->element < t1->element ){
            comparisonCounter++;
            return combineTrees( t2, t1 );
        }
        t2->nextSibling = t1->leftChild;
        t2->parent = t1; //set the parent node of the previous
        
        t1->leftChild = t2;
        t1->parent = nullptr; // becomes the  root of subtree/ignore assignment of nullptr
        assignmentCounter+=3;//above assignments
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    template <typename Comparable>
    void BinomialQueue<Comparable>::makeEmpty( BinomialNode<Comparable> * & t )
    {
        if( t != nullptr )
        {   // delete left and right child recursively 
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    template <typename Comparable>
    BinomialNode<Comparable> * BinomialQueue<Comparable>::clone( BinomialNode<Comparable> * t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinomialNode<Comparable>{ t->element, clone( t->leftChild ), clone( t->nextSibling ), clone(t->parent) };
    }


