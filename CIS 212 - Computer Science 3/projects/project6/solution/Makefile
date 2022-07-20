CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=exerciseStack balanceCheck

all: $(PROGRAMS)

exerciseStack: exerciseStack.o
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

balanceCheck: balanceCheck.o
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

exerciseStack.o: exerciseStack.c
balanceCheck.o: balanceCheck.c

clean:
	rm -f *.o $(PROGRAMS)
