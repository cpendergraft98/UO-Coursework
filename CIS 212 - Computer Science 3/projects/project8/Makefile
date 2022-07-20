CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
PROGRAMS=sorttest cskmtest wordfreq
OBJECTS=sort.o
LIBRARIES=-lADTs

all: $(PROGRAMS)

sorttest: sorttest.o sort.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

cskmtest: cskmtest.o sort.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

wordfreq: wordfreq.o sort.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

sorttest.o: sorttest.c sort.h
cskmtest.o: cskmtest.c sort.h
wordfreq.o: wordfreq.c sort.h

clean:
	rm -f $(PROGRAMS) $(OBJECTS) sorttest.o cskmtest.o wordfreq.o
