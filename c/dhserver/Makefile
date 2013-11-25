CC = gcc
LIBS = -lpthread

all: main http

http: http.o tpool.o
	${CC} http.o tpool.o -o http ${LIBS}

http.o: http.c
	${CC} -c http.c

main: main.o tpool.o
	${CC} main.o tpool.o -o main ${LIBS}

main.o: main.c
	${CC} -c main.c

tpool.o: tpool.c
	${CC} -c tpool.c

clean:
	rm *.o main http
