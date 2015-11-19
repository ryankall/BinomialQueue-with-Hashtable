CC=g++
C++FLAGS=-Wall -std=c++11 -pedantic

AVL_OBJ=main.o
PROG=Homework_2

%.o : %.cpp
	$(CC)  -c $< -o $@ $(C++FLAGS)

all:
	make $(PROG)
	
$(PROG): $(AVL_OBJ)
	$(CC) $(C++FLAG) -o $@ $(AVL_OBJ)




clean:
	(rm -f *.o;)
	rm -f $(PROG)
	
