all: build

build: clean
	mkdir -p ./bin
	g++ -std=c++17 -O3 -Wall -o ./bin/p2 src/*.cpp p2.cpp -Iinclude -lncurses
clean:
	rm -f ./bin/p2
