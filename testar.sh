#!/bin/bash
set -e

# define an int var
declare -i i=0
#g++ src/*.cpp -o pccm -Wall -Werror -std=c++20 -fopenmp

for variable in {0..4}
do
  ./src/bin/Debug/net8.0/src g-5-6.txt "$variable" > out.txt
  diff out.txt "g-5-6-$variable.out" -w
done

echo "Teste 5-6 passou"


for variable in {0..9}
do
  ./src/bin/Debug/net8.0/src g-10-30.txt "$variable" > out.txt
  diff out.txt "g-10-30-$variable.out" -w
done

echo "Teste 10-30 passou"


for variable in {0..4}
do
  ./src/bin/Debug/net8.0/src g-neg-c-5-6.txt "$variable" > out.txt
  diff out.txt "g-neg-c-5-6-$variable.out" -w -I "C"
done

echo "Teste c-neg-5-6 passou"

for variable in {0..9}
do
  ./src/bin/Debug/net8.0/src g-neg-c-10-30.txt "$variable" > out.txt
  diff out.txt "g-neg-c-10-30-$variable.out" -w -I "C" -I "E"
done

echo "Teste c-neg-10-30 passou"

./src/bin/Debug/net8.0/src g-100-300.txt 12 > out.txt
diff out.txt "g-100-300-12.out" -w
./src/bin/Debug/net8.0/src g-100-300.txt 37 > out.txt
diff out.txt "g-100-300-37.out" -w
./src/bin/Debug/net8.0/src g-100-300.txt 84 > out.txt
diff out.txt "g-100-300-84.out" -w
echo "g-100-300 passou"
./src/bin/Debug/net8.0/src g-100-1000.txt 12 > out.txt
diff out.txt "g-100-1000-12.out" -w
echo "teste  100 1000 12 passou"
./src/bin/Debug/net8.0/src g-100-1000.txt 37 > out.txt
diff out.txt "g-100-1000-37.out" -w
echo "teste  100 1000 37 passou"
./src/bin/Debug/net8.0/src g-100-1000.txt 84 > out.txt
diff out.txt "g-100-1000-84.out" -w
echo "g-100-1000 passou"
echo "g 1000-10000 comecando"
./src/bin/Debug/net8.0/src g-1000-10000.txt 31 > out.txt
diff out.txt "g-1000-10000-31.out" -w
echo "g-1000-10000 31 passou"
./src/bin/Debug/net8.0/src g-1000-10000.txt 265 > out.txt
diff out.txt "g-1000-10000-265.out" -w
echo "g-1000-10000 265 passou"
./src/bin/Debug/net8.0/src g-1000-10000.txt 403 > out.txt
diff out.txt "g-1000-10000-403.out" -w
echo "g-1000-10000 403 passou"
./src/bin/Debug/net8.0/src g-1000-10000.txt 697 > out.txt
diff out.txt "g-1000-10000-697.out" -w
echo "g-1000-10000 697 passou"
./src/bin/Debug/net8.0/src g-1000-10000.txt 812 > out.txt
diff out.txt "g-1000-10000-812.out" -w
echo "g-1000-10000 812 passou"
./src/bin/Debug/net8.0/src g-1000-10000.txt 963 > out.txt
diff out.txt "g-1000-10000-963.out" -w
echo "g-1000-10000 passou"


