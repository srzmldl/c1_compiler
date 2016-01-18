for((i=1;i<=30;i++))
{
    wget 'http://www.ida.liu.se/~erini02/detect/bench/orig'$i'.cc'
    wget 'http://www.ida.liu.se/~erini02/detect/bench/plag'$i'.cc'
}
wget 'http://www.ida.liu.se/~erini02/detect/bench/readme.txt'