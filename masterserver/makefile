
CC=gcc
#CC=egcs
CFLAGS=-Wall

all: eechmaster
eechmaster: eechmaster.o
	$(CC) $(CFLAGS) -o eechmaster eechmaster.o 
#netstuff.o: netstuff.c netstuff.h
#	$(CC) $(CFLAGS) -c netstuff.c
eechmaster.o: eechmaster.c
	$(CC) $(CFLAGS) -c eechmaster.c
clean:
	rm *.o;rm eechmaster
install:
	cp eechmaster /usr/local/bin
