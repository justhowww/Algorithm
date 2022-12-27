# CC and CFLAGS are varilables
CC = g++
STD = -std=c++11
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: graph_opt.o dgraph_opt.o main_opt.o disjoint_opt.o
			$(CC) $(OPTFLAGS) graph_opt.o dgraph_opt.o main_opt.o disjoint_opt.o  -o bin/cb
main_opt.o 	   	: src/main.cpp
			$(CC) $(STD) $(CFLAGS) $<  -o $@
graph_opt.o	:src/graph.cpp src/graph.h 
			$(CC) $(STD) $(CFLAGS) $(OPTFLAGS) $< -o $@

dgraph_opt.o	:src/dgraph.cpp src/graph.h 
			$(CC) $(STD) $(CFLAGS) $(OPTFLAGS) $< -o $@

disjoint_opt.o	:src/disjoint.cpp src/graph.h 
			$(CC) $(STD) $(CFLAGS) $(OPTFLAGS) $< -o $@



# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

