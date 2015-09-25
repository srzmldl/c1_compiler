# This Makefile requires GNU make.
# replace indent with tab.
SHELL = /bin/sh
CC = g++ -g
LEX = flex
PROGRAM = c1c
BIN = bin
SRC = src
INC = include
CONF = config
CFLAGS = -I ${INC}
LFLAGS =
YFLAGS =

default:: ${BIN}/c1c

${BIN}/c1c: ${BIN}/lexer.o ${BIN}/main.o ${BIN}/tok.o
	${CC} ${CFLAGS} -o $@ $^	

${SRC}/lexer.cpp: ${CONF}/lexer.lex
	@mkdir -p ${SRC}
	${LEX} ${LFLAGS} -o $@ $<

${BIN}/lexer.o: ${SRC}/lexer.cpp ${INC}/tok.h
	@mkdir -p ${BIN}
	${CC} ${CFLAGS} -c -o $@ $<

${BIN}/tok.o: ${SRC}/tok.cpp
	@mkdir -p ${BIN}
	${CC} ${CFLAGS} -c -o $@ $<

${BIN}/main.o: ${SRC}/main.cpp ${INC}/tok.h ${BIN}/lexer.o
	@mkdir -p ${BIN}
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY: clean
clean:
	-rm -f ${BIN}/*.o ${SRC}/lexer.cpp