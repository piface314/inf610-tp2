TARGET := inf610-tp2
CC := g++
CCFLAGS := -O2 -Wall -g -std=c++17
LDFLAGS := -Wall -lpthread -lm -ldl -lz -lncurses -rdynamic

.PHONY: all clean

all: obj bin bin/$(TARGET)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

bin/$(TARGET): obj/main.o obj/graph-rep.o obj/inc-matrix.o obj/adj-matrix.o obj/adj-list.o
	$(CC) -o bin/$(TARGET) obj/* $(LDFLAGS)

obj/main.o: src/main.cpp src/*.hpp
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

obj/graph-rep.o: src/graph-rep.hpp src/graph-rep.cpp src/list.hpp
	$(CC) -c $(CCFLAGS) src/graph-rep.cpp -o obj/graph-rep.o

obj/inc-matrix.o: src/inc-matrix.hpp src/inc-matrix.cpp src/list.hpp
	$(CC) -c $(CCFLAGS) src/inc-matrix.cpp -o obj/inc-matrix.o

obj/adj-matrix.o: src/adj-matrix.hpp src/adj-matrix.cpp src/list.hpp
	$(CC) -c $(CCFLAGS) src/adj-matrix.cpp -o obj/adj-matrix.o

obj/adj-list.o: src/adj-list.hpp src/adj-list.cpp src/list.hpp
	$(CC) -c $(CCFLAGS) src/adj-list.cpp -o obj/adj-list.o

clean:
	rm -vf obj/* bin/*
