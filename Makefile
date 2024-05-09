CFLAGS=-Wall
NUM_TEST=6

dag: src/main.c list.o graph.o util.o args.o
	gcc $(CFLAGS) -o dag src/main.c args.o util.o graph.o list.o

test: tests/test.c list.o graph.o
	gcc $(CFLAGS) -o test tests/test.c list.o graph.o

graph.o: src/graph.c src/graph.h
	gcc $(CFLAGS) -c src/graph.c

list.o: src/list.c src/list.h
	gcc $(CFLAGS) -c src/list.c

util.o: src/util.c src/util.h
	gcc $(CFLAGS) -c src/util.c

args.o: src/args.c src/args.h
	gcc $(CFLAGS) -c src/args.c


.PHONY: validation-test
validation-test:
	make dag-walk
	bash tests/test.sh dag-walk $(NUM_TEST)
	make clean

.PHONY: unit-test
unit-test:
	make test
	./test
	make clean

.PHONY: clean
clean:
	rm *.o
	rm dag
	rm test
