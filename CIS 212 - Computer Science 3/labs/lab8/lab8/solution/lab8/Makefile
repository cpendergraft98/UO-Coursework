CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=lab8

all: $(PROGRAMS)

lab8: llistprioqueue.o lab8.o
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

#llistprioqueue.o: llistprioqueue.c llistprioqueue.h prioqueue.h
lab8.o: lab8.c llistprioqueue.c llistprioqueue.h prioqueue.h

clean:
	rm -f *.o $(PROGRAMS)
