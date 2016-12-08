OBJECTS = main.o print.o node.o BST.o
HEADERS = node.h BST.h

proj3: $(OBJECTS) #compile target
	g++ -std=c++11 -g $^ -o $@

%.o: %.cpp $(HEADERS) #compile object files
	g++ -std=c++11 -g -c $< -o $@

clean: # clean older builds
	rm -f *.o proj3
