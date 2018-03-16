CXX = g++
CXXFLAGS = -Wall -g

main: main.o AVL.o
	$(CXX) $(CXXFLAGS) -o main main.o AVL.o

main.o: main.cpp AVL.h
	$(CXX) $(CXXFLAGS) -c main.cpp

AVL.o: AVL.h


clean:
	rm -rf *.o main


