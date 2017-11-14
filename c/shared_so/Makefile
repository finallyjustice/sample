all:
	gcc -c -Wall -Werror -fpic -g foo.c
	gcc -shared -o libfoo.so -g foo.o
	gcc -Wall -o binary binary.c -lfoo -L. -g

clean:
	rm -rf binary libfoo.so foo.o
