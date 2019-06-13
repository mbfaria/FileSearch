CXX		  := g++ -w
CXX_FLAGS := -Wall -Wextra -std=c++14 -ggdb


all: bin/main bin/teste

clean:
	rm -rf bin/*

run: bin/main
	clear
	./bin/main

teste: bin/teste
	clear
	./bin/teste

bin/filesearch.o: src/filesearch.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

bin/main: bin/filesearch.o src/main.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

bin/teste: bin/filesearch.o src/teste.cpp
	$(CXX) $(CXX_FLAGS) -I include/ $^ -o $@