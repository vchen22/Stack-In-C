clean:
	rm -f *.run

test: clean test_stack.run
	valgrind --leak-check=full --undef-value-errors=no ./test_stack.run

test_stack.run: test_stack.c stack.c stack.h
	gcc -g -Wall -std=c99 -o test_stack.run stack.c test_stack.c cutest/CuTest.c
