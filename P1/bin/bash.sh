for file in ../src/*.c
do 
    name=${file%.*}
    gcc -o $name $file
    echo $name
    ./$name
    echo -e '\n'
    rm $name
done 
