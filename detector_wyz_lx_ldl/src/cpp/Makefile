#Should specify the directories of clang's source and build.
LLVM_HOME=/home/bryan/llvm-3.6.0

CC=clang
LLVM_CONFIG=llvm-config-3.6
LIB=../../lib
BIN=../../bin
all: PrintCFG_BFS.so ast
PrintCFG_BFS.so: PrintCFG_BFS.cpp
	$(CC) -shared  `$(LLVM_CONFIG) --cxxflags --ldflags --libs support` -I$(LLVM_HOME)/build/tools/clang/include -I$(LLVM_HOME)/tools/clang/include PrintCFG_BFS.cpp -o PrintCFG_BFS.so
	@mkdir -p $(LIB)
	cp PrintCFG_BFS.so $(LIB)
ast: ast.cpp
	g++ -std=c++11 -Wall -o $(BIN)/ast ast.cpp -g -lm
.PHONY: clean
clean:
	rm -f PrintCFG_BFS.so $(LIB)/PrintCFG_BFS
	rm -f $(BIN)/ast now.cpp warn.txt
