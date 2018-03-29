morton_traverse: morton.o
	gcc -o morton_traverse morton.o

morton.o: src/morton.c
	gcc -c src/morton.c

clean: 
	rm morton.o morton_traverse
