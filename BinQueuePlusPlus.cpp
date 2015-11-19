/* 
 * File:   BinQueuePlusPlus.cpp
 * Author: Ryan Kallicharran
 * 
 * Created on November 9, 2015, 12:52 PM
 */

#include "BinQueuePlusPlus.h"

BinQueuePlusPlus::BinQueuePlusPlus() {
    //build binomial Queue  from word file.
    readFile();
}

BinQueuePlusPlus::~BinQueuePlusPlus() {
    //deletes the queue
    makeEmpty();
}

void BinQueuePlusPlus::insert( string& key){
    
    //insert the word into binomialQueue
    Pointer =  bQueue.insert(key);
    //insert pair into table
    table.insert(key, Pointer);    
}

void BinQueuePlusPlus::makeEmpty(){
    //empty the BinomialQueue
    bQueue.makeEmpty();
    //Empty hash table
    table.makeEmpty();     
}

bool BinQueuePlusPlus::readFile(){
    
    //opens file we are reading
    std::ifstream myFile;
    myFile.open("words.txt", std::ios_base::in);


    //check if file exists
    if(!myFile.good()){
        std::cout<<"Error: file does not exist"<<std::endl;
        exit(1);
    }

    cout<<"Building Queue..."<<endl;

    string curr_line;

    while(getline(myFile, curr_line)){
       
        insert(curr_line); //insert the current word
    }//end while
    
    //close file
    myFile.close();
    
    cout<<"Queue Build finished."<<endl;
    
    return true;
}

//comparison count of insertion
int BinQueuePlusPlus::getComparCount(){
   return  bQueue.getComparCount();
}

//assignment count of insertion
int BinQueuePlusPlus::getAssignCount(){
   return  bQueue.getAssignCount();
}

string BinQueuePlusPlus::deleteMin(){
    
    string found;//hold our min key
    if(!bQueue.isEmpty()){
        found = bQueue.findMin();//save min for return
        bQueue.deleteMin();//deletes the min 
        table.remove(found);//update hash table
    }else{
        found = "Queue is empty";
    }
    
    return found;
    
}

bool BinQueuePlusPlus::contains(string & key){
    //check is key in hash table is  nullptr
    if(find(key) == nullptr){
        return false;
    }else
        return true;
    
}


//moves a key to from of queue and then deletes from queue
bool BinQueuePlusPlus::remove(string & key)
{
    //check if the key exist first
    if (!table.contains(key))
        return false;
    
    BinomialNode<string>* x = table.find(key);

    
    //lowest string
    string lowest = "0";
    //get the key want to remove to front of the queue
    decreaseKey(x,lowest);
            
    //delete key from queue
    bQueue.deleteMin();
    
    //delete key from table
    table.remove(key);
    
    //check again if key exist in table
    if (table.find(key)== nullptr)
    {
        return true;
    }
    return false;
}



//////////////////////////////////////////////////////////////////////////////
//                         Protected Function                               //
//////////////////////////////////////////////////////////////////////////////

 /*
  * Finds a given key in the hash table and returns the pointer connected 
  * to that key
  */
BinomialNode<string>* BinQueuePlusPlus::find(  string & key ) 
{
    //find the word in hash table if exist
    BinomialNode<string>* temp = table.find(key);
    return temp; 
}


/*
  * Takes a certain key and move it to the front of the queue
  * by percolating up the binomialQueue
  */
 bool BinQueuePlusPlus::decreaseKey( BinomialNode<string>* keyNode, string k){
     
    
     string save = keyNode->element;
          
    //check if new key is greater than key node if it is there is an error
    if (k > keyNode->element) 
        return false;  

    
    //set key node to new key
    keyNode->element = k; 

    //temp node declaration
    BinomialNode<string>* tempKeyNode = keyNode; 
    BinomialNode<string>* tempKeyNodePar = tempKeyNode->parent; 
    
    //handles percolation of the nodes
    while (tempKeyNodePar != nullptr && tempKeyNode->element < tempKeyNodePar->element) 
    { 
        string temp = tempKeyNode->element; 
        //swap element with parent and child
        tempKeyNode->element = tempKeyNodePar->element; 
        tempKeyNodePar->element = temp; 
        
        //update pointer in table for swapped elements
        table.update(tempKeyNode->element, tempKeyNode);
        table.update(tempKeyNodePar->element, tempKeyNodePar);
        
        //swap nodes with parent with child
        tempKeyNode = tempKeyNodePar;    
        tempKeyNodePar = tempKeyNode->parent; 
           
    }//end loop 

    return true; 
        
     
 }
 

  
