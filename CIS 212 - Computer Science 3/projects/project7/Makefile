CLFAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=exerciseQueue

all: $(PROGRAMS)

exerciseQueue: exerciseQueue.o llistqueue.o
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

llistqueue.o: llistqueue.c
exerciseQueue.o: exerciseQueue.c llistqueue.c

clean:
	rm -f *.o $(PROGRAMS)