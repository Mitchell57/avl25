CXX = g++
CXXFLAGS = -Wall -g

main: main.o AVL.o
	$(CXX) $(CXXFLAGS) -o main main.o AVL.o

main.o: main.cpp AVL.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tree25: tree25.o
	$(CXX) $(CXXFLAGS) -o tree25 tree25.o

tree25.o: tree25.cpp
	$(CXX) $(CXXFLAGS) -c tree25.cpp

AVL.o: AVL.h



clean:
	rm -rf *.o main


