CXX = g++
CXXFLAGS = -Wall -g

main: main.o AVL.o tree25.o
	$(CXX) $(CXXFLAGS) -o main main.o AVL.o tree25.o

main.o: main.cpp AVL.h tree25.h entry.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tree25.o: tree25.cpp tree25.h entry.h
	$(CXX) $(CXXFLAGS) -c tree25.cpp

AVL.o: AVL.h



clean:
	rm -rf *.o main


