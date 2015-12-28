#!/bin/sh

# Generate IR
./demo 2> 'test.ll'

# Generate Obj
llc -filetype=obj test.ll -o test.o

# Link
clang test.o libdemo.a -o test

# run
./test
