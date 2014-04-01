CC=g++
LIB=-I /usr/include/mysql -lmysqlclient

all: Main

Main: Main.cc DBManager.cc DBManager.h
	${CC} Main.cc DBManager.cc -o Main ${LIB}

clean:
	rm -f Main
