flags = -Wall -O2 

all: clean tree

tree: tree.o
	gcc ${flags} $^ -o $@

tree.o: tree.c
	gcc ${flags} -c $^

clean:
	rm -rf *.o tree