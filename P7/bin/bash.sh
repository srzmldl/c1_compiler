#!/bin/sh
./c1 a.in
llc -filetype=obj c1.ll -o test.o
clang 
clang++ test.o libmy.a -o test
./test