clang++ a.cpp -S -emit-llvm
llc -o b.cpp -march=cpp a.ll