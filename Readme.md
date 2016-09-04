``
Files-----------------------------------------------------------
  BinQueuePlusPlus.cpp 	
	BinQueuePlusPlus.h 	
	BinomialNode.h 	
	BinomialQueue.cpp 	
	BinomialQueue.h 	
	Makefile 
	QuadraticProbing.cpp 	
	QuadraticProbing.h 	
	dsexceptions.h 	
	main.cpp
	--------------------------------------------------------------
``	
Complete the following tasks:

1. Implement the binomial queue. Implement a hash-table of the keys that are already
in the priority queue. So, for any pair (key, pointer), where pointer is the pointer
of the the node that holds key in the priority queue, hash on the key, and store the
pair (key, pointer) in your hash table.

2. Count and print out the total number of comparisons and assignments executed for
the insertions of all the N elements into the binomial queue.

3. Test the deleteMin() operation by applying a sequence of 10 deleteMin() and by
printing out the result.

4. Test the function find() as follows: Prompt the user to input a string key. Execute
the private function find(key). If find returns a pointer to a node that indeed holds
key printout that find() was successful. Otherwise, printout that find() did not find
the key.

5. You are ready to implement now the remove and decreaseKey operations. Keep in
mind that remove is a simple extension of decreaseKey: first decrease the key of the
target so that it percolates to the top (i.e., becomes the minimum key), then simply
call deleteMin. Note that percolating up involves accessing (and possibly moving) the
parent node. You may modify the given code so that each node keeps a pointer to its
parent.

6. Test your implementation by applying a sequence of remove(key) operations, and
verify their correctness. For instance after remove(key), find(key) should return “not
found”. Prompt the user 5 times to input a key. Execute the remove(key)operation
and verify (by printing whether the removal was successful or not).








