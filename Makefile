CXX = g++
CXXFLAGS = -c -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

all: main

main.o: main.cpp Display.hpp  
	$(CXX) $(CXXFLAGS) -o main.o main.cpp
	
ia.o: ia.cpp ia.hpp
	$(CXX) $(CXXFLAGS) -o ia.o ia.cpp

board.o: board.cpp board.hpp 
	$(CXX) $(CXXFLAGS) -o board.o board.cpp

List.o: List.cpp List.hpp 
	$(CXX) $(CXXFLAGS) -o List.o List.cpp

struct.o: struct.cpp struct.hpp 
	$(CXX) $(CXXFLAGS) -o struct.o struct.cpp

Display.o: Display.cpp Display.hpp struct.hpp ia.hpp
	$(CXX) $(CXXFLAGS) -o Display.o Display.cpp

main: main.o Display.o struct.o ia.o board.o List.o
	$(CXX) -o main main.o Display.o struct.o ia.o board.o List.o $(SFMLFLAGS)

clean:	
	rm -f *.o
	