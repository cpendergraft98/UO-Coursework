CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs

exerciseStack: exerciseStack.o
	gcc $(CFLAGS) $(LDFLAGS) -o exerciseStack $^ $(LIBRARIES)
exerciseStack.o: exerciseStack.c

clean:
	rm -f exerciseStack exerciseStack.o
