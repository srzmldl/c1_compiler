clang++ -g src/kaleidoscope.cpp -o bin/kaleidoscope
echo -e 'Runing keleidoscope\n plz see the input in test/keleidoscope.in'
./bin/kaleidoscope <test/kaleidoscope.in
rm bin/kaleidoscope


echo -e 'now check my c1 by flex'
make

for file in test/*.c
do 
    name=${file%.*}'.out';
    echo -e 'running for'  $file
    ./bin/c1c $file >$name
    echo -e 'see answer in'  $name
done 

make clean
rm bin/c1c