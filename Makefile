CC = g++
CCFLAGS = -c -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

all: main

main.o: main.cpp display.hpp 
	${CC} ${CCFLAGS} -o main.o main.cpp

struct.o: struct.cpp struct.hpp 
	${CC} ${CCFLAGS} -o struct.o struct.cpp

display.o: display.cpp display.hpp struct.hpp
	${CC} ${CCFLAGS} -o display.o display.cpp

main: main.o display.o struct.o
	${CC} -o main main.o display.o struct.o ${SFMLFLAGS}

clean:
	rm -f *.o