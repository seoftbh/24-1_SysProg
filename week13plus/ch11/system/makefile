CC = gcc
CFLAGS = -Wall -g

all: systemCall

system.o: system.c
	$(CC) $(CFLAGS) -c system.c

systemCall: systemCall.c system.o
	$(CC) $(CFLAGS) systemCall.c system.o -o systemCall

clean:
	rm -f *.o systemCall
