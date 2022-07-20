CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=test

all: $(PROGRAMS)

test: test.o student.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

student.o: student.c student.h
studentlist.o: studentlist.c studentlist.h student.h
test.o: test.c student.h

clean:
	rm -f *.o $(PROGRAMS)
