CC=g++
CFLAGS= -std=c++2a -Wall -Wextra -Wshadow -Wpedantic -O3

all: build

clean:
	rm -f ../bin/*

../bin/%.o: %.cpp
	mkdir -p ../bin
	$(CC) -c $(CFLAGS) $< -o ../bin/$@

build: ../bin/main.o
	mkdir -p ../bin
	$(CC) -o ../bin/main ../bin/main.o

run: build
	@../bin/main

install: ../bin/main
	sudo cp ../bin/main /usr/local/bin/roman
