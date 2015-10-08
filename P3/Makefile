CC=clang++
CFLAGS=-I include

bin/toy: bin/toy.o bin/dumpdot.o
	$(CC) -o $@ $^ `llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native`

bin/toy.o: src/toy.cpp include/ast.h include/dumpdot.h
	@mkdir -p bin
	$(CC) -c -o $@ $< $(CFLAGS) `llvm-config --cxxflags`

bin/dumpdot.o: src/dumpdot.cpp include/dumpdot.h
	@mkdir -p bin
	$(CC) -c -o $@ $< $(CFLAGS) `llvm-config --cxxflags`

.PHONY:clean
clean:
	-rm -f bin/toy bin/*.o
	-rm -f watch.png toy.dot
