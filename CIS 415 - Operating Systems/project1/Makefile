CFLAGS=-W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
PROGS=uspsv1 uspsv2 uspsv3 uspsv4
LIBRARIES=-lADTs -lncurses

all: $(PROGS)

uspsv1: uspsv1.o p1fxns.o
	gcc $(LDFLAGS) -o $@ $^

uspsv2: uspsv2.o p1fxns.o
	gcc $(LDFLAGS) -o $@ $^

uspsv3: uspsv3.o p1fxns.o $(LIBRARIES)
	gcc $(LDFLAGS) -o $@ $^

uspsv4: uspsv4.o p1fxns.o $(LIBRARIES)
	gcc $(LDFLAGS) -o $@ $^

clean: 
	rm -f *.o $(PROGS)

uspsv1.o: uspsv1.c p1fxns.h
uspsv2.o: uspsv2.c p1fxns.h
uspsv3.o: uspsv3.c p1fxns.h
uspsv4.o: uspsv4.c p1fxns.h
p1fxns.o: p1fxns.c p1fxns.h
