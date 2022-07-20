CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs

lab7: lab7.o
	gcc $(CFLAGS) $(LDFLAGS) -o lab7 $^ $(LIBRARIES)
lab7.o: lab7.c

clean:
	rm -f lab7 lab7.o
