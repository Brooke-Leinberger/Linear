HEADERS = vector.h matrix.h unit_tests.h

default: test

prime:	vector.o main.o matrix.o $(HEADERS)
	gcc -g -o linear unit_tests.o vector.o main.o matrix.o -lm

test: vector.o main.o matrix.o unit_tests.o $(HEADERS)
	gcc -g -o test unit_tests.o vector.o main.o matrix.o -lm

unit_tests.o: unit_tests.c $(HEADERS)
	gcc -g -c -Wall unit_tests.c

main.o:	main.c unit_tests.o $(HEADERS)
	gcc -g -c -Wall main.c

vector.o: vector.c $(HEADERS)
	gcc -g -c -Wall vector.c

matrix.o: matrix.c $(HEADERS)
	gcc -g -c -Wall matrix.c



clean:
	-rm -f vector.o
	-rm -f matrix.o
	-rm -f unit_tests.o
	-rm -f main.o
	-rm -f test
	-rm linear
