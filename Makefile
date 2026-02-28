INCLUDES= -I ./include
OBJECTS= ./build/fire.o
FLAGS= -g 

all:${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} -c ./src/fire.c -o ./build/fire.o

	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -L ./lib -lmingw32 -lSDL3 -o ./bin/main


run:
	./bin/main

clean:
	rm ./bin/main
	rm ./build/*