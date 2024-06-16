all: build

build: clean
	mkdir -p ./bin
	g++ -std=c++17 -O3 -Wall -o ./bin/p3 src/*.cpp p3.cpp -Iinclude -lncurses
clean:
	rm -f ./bin/p3
