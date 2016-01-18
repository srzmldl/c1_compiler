mkdir -p input
mkdir -p output

OUTPUT=input
for filePath in ./codes/*
do
	filenameTmp=${filePath##*/}
	#echo $filenameTmp
	filename=${filenameTmp%.*}
	echo "$filename-------------------:"
	clang -cc1 -w -load ../../lib/PrintCFG_BFS.so -analyze -analyzer-checker=codeclone.PrintCFG_BFS ${filePath} 2>${OUTPUT}/${filename}.txt
done
#python ../../src/py/interaction.py
