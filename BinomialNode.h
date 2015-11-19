/* 
 * File:   BinomialNode.h
 * Author: Ryan Kallicharran
 *
 * Created on November 9, 2015, 5:28 PM
 */

#ifndef BINOMIALNODE_H
#define	BINOMIALNODE_H
#include <iostream>
using namespace std;

template<typename Comparable>
struct BinomialNode
    {
    public:
        Comparable    element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        BinomialNode *parent;

        BinomialNode(const  Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
          : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent { p } { }
        
        BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
          : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parent{ p } { }
    };

#endif	/* BINOMIALNODE_H */
