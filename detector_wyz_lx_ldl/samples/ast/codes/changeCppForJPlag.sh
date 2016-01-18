for file in *.cc
do
	name=${file%.*}
	newName=$name'.cpp'
	mv $file $newName
done 
