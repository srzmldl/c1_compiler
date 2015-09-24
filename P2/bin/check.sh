clang++ -g src/kaleidoscope/kaleidoscope.cpp -o bin/kaleidoscope
echo -e 'here is my output of keleidoscope\n plz see the input in test/keleidoscope.in'
./bin/kaleidoscope <test/kaleidoscope.in
rm bin/kaleidoscope