/**
 * Author : Ryan Kallicharran
 * Program : test the combined BinomialQueue and hash table 
 *           functions
 * date created : Nov 16, 2015
 */
#include <iostream>
#include "BinQueuePlusPlus.h"

using namespace std;

 

//Prompts the user for a key then lets them know if it exist in the queue.
//@param a BinQueuePlusPlus
//@return nothing
void runFindTask(BinQueuePlusPlus &ourQueue);

//Run the delete min function 10 times  and print result to user
//@param a BinQueuePlusPlus
//@return nothing
void runDeleteTask(BinQueuePlusPlus &ourQueue);

//Run the delete min function 10 times  and print result to user
//@param a BinQueuePlusPlus
//@return nothing
void runRemoveTask(BinQueuePlusPlus &ourQueue);

int main( )
{
   
    //create queue
    BinQueuePlusPlus ourQueue;
    //tells user findings
    cout<<"Comparison count after insertion: " <<ourQueue.getComparCount()<<endl;   
    cout<<"Assignment count after insertion: " <<ourQueue.getAssignCount()<<endl;

    //run tasks
    runDeleteTask(ourQueue);
    runFindTask(ourQueue);
    runRemoveTask(ourQueue);
    
    
    
    
    return 0;
}

void runDeleteTask(BinQueuePlusPlus &ourQueue){
    
    cout<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<"**                   Running Delete Task                    **"<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<endl;
    
    cout<< "The following item has been deleted from the queue: "<<endl;
    for(int x = 1; x <= 10; x++){
        //run the delete min 10 times
        cout<<  ourQueue.deleteMin()<<endl;
    }
    
    cout<< "Test the deleteMin() operation has been completed."<<endl;
}


void runFindTask(BinQueuePlusPlus &ourQueue){
    
  
    cout<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<"**                  Running Find Task                       **"<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<endl;
    
    string answer;
    do{
        string searchKey;
        //prompt user for key
        cout<<"Please enter a key to find: ";
        cin>>searchKey;
        cout<<"Searching for:  " << searchKey <<endl;
        
        //check if key is in queue
        if(ourQueue.contains(searchKey)){
            cout<< "The find function was successful!"<<endl;
        }else{
            cout<< "The word entered does not exist the database!"<<endl;
        }
        
        
        
        
        cout<<"To search again enter 'y' else hit any key: ";
        cin>>answer;
        cout<<endl;
        
    }while(answer[0] == 'y' || answer[0] == 'Y');
    
    cout<<"Find Task has ended..." <<endl;
        
}

void runRemoveTask(BinQueuePlusPlus& ourTree)
{
    cout<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<"**                 Running Remove Task                      **"<<endl;
    cout<<"**************************************************************"<<endl;
    cout<<endl;
    

    string input;
    for(int i = 1; i<=5; i++){
        
        //prompt user for key
        cout<<i<<") Please enter a key for removal: ";
        cin>>input;
        
        //check if key is in queue
        if (ourTree.contains(input) == false)
        {
            cout<<"KEY : "<<input<<"  does not exist in queue"<<endl;
        }
        else{
            //check if the remove was successful
            if(ourTree.remove(input))
            cout<<"KEY : "<<input<<" : checked & successfully deleted"<<endl;
            
            else
                cout<<"unsuccessful removal"<<endl;
        }
        
        cout<<endl;
    }//end loop
    
    cout<<"Remove Task has ended..." <<endl;
       
}
