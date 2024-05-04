CXX = g++
CXXFLAGS = -c -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

all: main

main.o: main.cpp Display.hpp 
	$(CXX) $(CXXFLAGS) -o main.o main.cpp

struct.o: struct.cpp struct.hpp 
	$(CXX) $(CXXFLAGS) -o struct.o struct.cpp

Display.o: Display.cpp Display.hpp struct.hpp
	$(CXX) $(CXXFLAGS) -o Display.o Display.cpp

main: main.o Display.o struct.o
	$(CXX) -o main main.o Display.o struct.o $(SFMLFLAGS)
	rm -f *.o
	