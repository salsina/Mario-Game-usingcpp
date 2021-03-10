CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: a.out

a.out: main.o Functions.o Mario.o Obstacle.o rsdl.o
	$(CC) main.o rsdl.o Functions.o Mario.o Obstacle.o $(CCFLAGS) -o a.out

main.o: src/rsdl.hpp Config.h Obstacle.h Mario.h Functions.h main.cpp
	$(CC) -c main.cpp -o main.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

Functions.o: src/rsdl.hpp Config.h Functions.cpp Functions.h Config.h
	$(CC) -c Functions.cpp -o Functions.o

Mario.o: Mario.h Mario.cpp Config.h Obstacle.h Functions.h src/rsdl.hpp
	$(CC) -c Mario.cpp -o Mario.o

Obstacle.o: src/rsdl.hpp Config.h Obstacle.h Obstacle.cpp Functions.h
	$(CC) -c Obstacle.cpp -o Obstacle.o

.PHONY: clean
clean:
	rm -r *.o