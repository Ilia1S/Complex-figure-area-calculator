CC = clang
CFLAGS = -Wall -Wextra -Werror

all: calc

calc: main.o functions.o
	$(CC) $(CFLAGS) -o calc main.o functions.o

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f calc *.o
