CC=clang++ -g -w 
LEX=lex
YACC=bison
CFLAGS=-I include
LLVMFLAGS=`llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native`
YFLAGS=
LFLAGS=

all: bin/c1 bin/libmy.a

bin/c1:  bin/lexer.o bin/parser.o bin/main.o bin/util.o bin/global.o bin/node.o bin/dumpdot.o bin/codegen.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LLVMFLAGS)

src/parser.cc include/tok.hh: config/parser.y
	$(YACC) $(YFLAGS) --defines=include/tok.hh -o src/parser.cc $<

bin/parser.o: src/parser.cc include/node.hh include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< $(LLVMFLAGS)

src/lexer.cc: config/lexer.l
	$(LEX) $(LFLAGS) -o $@ $<

bin/lexer.o: src/lexer.cc include/tok.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<  $(LLVMFLAGS)

bin/node.o: src/node.cc include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< $(LLVMFLAGS)

bin/main.o: src/main.cc include/tok.hh include/util.hh include/global.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< $(LLVMFLAGS)

bin/util.o: src/util.cc include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/global.o: src/global.cc include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<  $(LLVMFLAGS)

bin/codegen.o: src/codegen.cc include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -std=c++11 -c -o $@ $< $(LLVMFLAGS)

bin/dumpdot.o: src/dumpdot.cc include/dumpdot.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -std=c++11 -c -o $@ $< $(LLVMFLAGS)

bin/libmy.o: src/libmy.c
	@mkdir -p bin
	clang -c -o $@ $<
bin/libmy.a: bin/libmy.o
	@mkdir -p bin
	ar rcs $@ $<

.PHONY: clean
clean:
	rm -f bin/*.o src/lexer.cc src/parser.cc include/tok.hh bin/libmy.a
	rm -f *.png *.dot

