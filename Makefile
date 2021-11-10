main: mem.c
	gcc -g -Wall -fpic -c mem.c
	gcc -g -o libmem.so mem.o -shared
	gcc -g -o mem mem.c -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

clean:
	rm mem