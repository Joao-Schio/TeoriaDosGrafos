#!/bin/bash
set -e

# define an int var
declare -i i=0
g++ src/*.cpp -o pccm -Wall -Werror -std=c++20

for variable in {0..4}
do
  ./pccm g-5-6.txt "$variable" > out.txt
  diff out.txt "g-5-6-$variable.out" -w
done

echo "Teste 5-6 passou"


for variable in {0..9}
do
  ./pccm g-10-30.txt "$variable" > out.txt
  diff out.txt "g-10-30-$variable.out" -w
done

echo "Teste 10-30 passou"


for variable in {0..4}
do
  ./pccm g-neg-c-5-6.txt "$variable" > out.txt
  diff out.txt "g-neg-c-5-6-$variable.out" -w -I "C"
done

echo "Teste c-neg-5-6 passou"

for variable in {0..9}
do
  ./pccm g-neg-c-10-30.txt "$variable" > out.txt
  diff out.txt "g-neg-c-10-30-$variable.out" -w -I "C" -I "E"
done

echo "Teste c-neg-10-30 passou"

./pccm g-100-300.txt 12 > out.txt
diff out.txt "g-100-300-12.out" -w
./pccm g-100-300.txt 37 > out.txt
diff out.txt "g-100-300-37.out" -w
./pccm g-100-300.txt 84 > out.txt
diff out.txt "g-100-300-84.out" -w
echo "g-100-300 passou"
./pccm g-100-1000.txt 12 > out.txt
diff out.txt "g-100-1000-12.out" -w
echo "teste  100 1000 12 passou"
./pccm g-100-1000.txt 37 > out.txt
diff out.txt "g-100-1000-37.out" -w
echo "teste  100 1000 37 passou"
./pccm g-100-1000.txt 84 > out.txt
diff out.txt "g-100-1000-84.out" -w
echo "g-100-1000 passou"
./pccm g-1000-10000 31
diff a.out "g-1000-10000-31.out" -w
echo "g-1000-10000 31 passou"
./pccm g-1000-10000 265
diff a.out "g-1000-10000-265.out" -w
echo "g-1000-10000 265 passou"
./pccm g-1000-10000 403
diff a.out "g-1000-10000-403.out" -w
echo "g-1000-10000 403 passou"
./pccm g-1000-10000 697
diff a.out "g-1000-10000-697.out" -w
echo "g-1000-10000 697 passou"
./pccm g-1000-10000 812
diff a.out "g-1000-10000-812.out" -w
./pccm g-1000-10000 963
diff a.out "g-1000-10000-963.out" -w
echo "g-1000-10000 passou"


