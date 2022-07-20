CFLAGS=-W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
OBJECTS=wordperline.o
LIBRARIES=-lADTs

wordperline: $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

wordperline.o: wordperline.c

clean:
	rm -f $(OBJECTS) wordperline