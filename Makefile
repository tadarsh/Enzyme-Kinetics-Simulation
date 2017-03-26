all: bin/main

bin/main: sample/test.cpp obj/ssa.o
	g++ -o $@ $^ -Iinclude/

obj/ssa.o: src/SSA.cpp
	mkdir -p bin obj
	g++ -c $^ -o $@ -Iinclude/
