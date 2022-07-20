CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
OBJECTS=lab5.o
LIBRARIES=-lADTs -lm

lab5: $(OBJECTS)
	gcc $(CFLAGS) $(LDFLAGS) -o lab5 $^ $(LIBRARIES)
lab5.o: lab5.c

clean:
	rm -f lab5 $(OBJECTS)
