all: randfile.o
	gcc -o randfile randfile.o

randfile.o: randfile.c
	gcc -c randfile.c

run: all
	./randfile

clean:
	rm -f *.o
	rm -f *~