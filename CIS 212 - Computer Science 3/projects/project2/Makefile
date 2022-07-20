CFLAGS=-W -Wall 
PROGRAMS=lcnt wcnt ccnt wcfilter wcargs wc 
all: $(PROGRAMS)
	lcnt: lcnt.o 
		gcc -o lcnt $^ 
	wcnt: wcnt.o stsplit.o 
		gcc -o wcnt $^ 
	ccnt: ccnt.o 
		gcc -o ccnt $^ 
	wcfilter: wcfilter.o stsplit.o 
		gcc -o wcfilter $^ 
	wcargs: wcargs.o 
		gcc -o wcargs $^ 
	wc: wc.o stsplit.o 
		gcc -o wc $^ 
	stsplit.o: stsplit.c stsplit.h 
	lcnt.o: lcnt.c 
	wcnt.o: wcnt.c stsplit.h 
	ccnt.o: ccnt.c 
	wcfilter.o: wcfilter.c stsplit.h 
	wcargs.o: wcargs.c 
	wc.o: wc.c stsplit.h 
	clean: 
		rm -f $(PROGRAMS) *.o 