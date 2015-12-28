#!/bin/sh
make
echo 'test all kind of stmt:'
./bin/c1 test/test.c1 bin/c1.ll
llc -filetype=obj bin/c1.ll -o bin/test.o
clang bin/test.o bin/libmy.a -o bin/test
./bin/test

echo 'factorial of 120 and 10:'
./bin/c1 test/factorial.c bin/fac.ll
llc -filetype=obj bin/fac.ll -o bin/fac.o
clang bin/fac.o bin/libmy.a -o bin/fac
./bin/fac

echo 'picMax:'
./bin/c1 test/pickMax.c bin/max.ll
llc -filetype=obj bin/max.ll -o bin/max.o
clang bin/max.o bin/libmy.a -o bin/max
./bin/max
