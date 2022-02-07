#
# Macro definitions
#
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -fstack-protector-all -Werror
all: main.x tester.x program1.x


main.x: main.o array-print.o range-fill.o
	$(CC) main.o array-print.o range-fill.o -o main.x

tester.x: tester.o row-sum.o array-sum.o range-fill.o
	$(CC) tester.o row-sum.o array-sum.o range-fill.o -o tester.x

program1.x: program1.o row-compare.o
	$(CC) program1.o row-compare.o -o program1.x

program1.o: program1.c row-compare.h
	$(CC) $(CFLAGS) -c program1.c

tester.o: tester.c array-sum.h range-fill.h row-sum.h
	$(CC) $(CFLAGS) -c tester.c

main.o: main.c range-fill.h array-print.h
	$(CC) $(CFLAGS) -c main.c

row-compare.o: row-compare.c row-compare.h
	$(CC) $(CFLAGS) -c row-compare.c

array-sum.o: array-sum.c array-sum.h
	$(CC) $(CFLAGS) -c array-sum.c

range-fill.o: range-fill.c range-fill.h
	$(CC) $(CFLAGS) -c range-fill.c

array-print.o: array-print.c array-print.h
	$(CC) $(CFLAGS) -c array-print.c

row-sum.o: row-sum.c row-sum.h
	$(CC) $(CFLAGS) -c row-sum.c

clean:
	rm -f *.x *.o



