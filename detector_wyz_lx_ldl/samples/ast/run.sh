cd ../../src/cpp/
make ast 2> warn.txt
cd ../../bin/
./ast nocom ../samples/ast/codes/orig23.cpp ../samples/ast/codes/plag23.cpp
./ast com  ../samples/ast/codes/ ../samples/ast/jplag/jplag.txt ../samples/ast/moss/moss.txt