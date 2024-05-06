CC = g++
CCFLAGS = -c -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

all: main

main.o: main.cpp Display.hpp 
	${CC} ${CCFLAGS} -o main.o main.cpp

struct.o: struct.cpp struct.hpp 
	${CC} ${CCFLAGS} -o struct.o struct.cpp

Display.o: Display.cpp Display.hpp struct.hpp
	${CC} ${CCFLAGS} -o Display.o Display.cpp

main: main.o Display.o struct.o
	${CC} -o main main.o Display.o struct.o ${SFMLFLAGS}

clean:
	rm -f *.o
	