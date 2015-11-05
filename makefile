CFLAGS=-Wall -g -Werror -std=c11
LIBS= -lm

all:
	gcc $(CFLAGS) program.c -o program $(LIBS)


clean:
	rm -f program
	rm -f string
	rm -f file_utility
	rm -f arraylist
	rm -f map
