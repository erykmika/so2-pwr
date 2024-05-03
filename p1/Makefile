all: build

build: clean
	mkdir -p ./bin
	g++ -std=c++17 -O3 -Wall -o ./bin/p1 src/*.cpp p1.cpp -Iinclude -lncurses
clean:
	rm -f ./bin/p1
