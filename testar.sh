#!/bin/bash
set -e

# define an int var
declare -i i=0
g++ src/*.cpp -o pccm -Wall -Werror

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

