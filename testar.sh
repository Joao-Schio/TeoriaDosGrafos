#!/bin/bash
set -e

# define an int var
declare -i i=0
g++ src/*.cpp -o pccm -Wall -Werror
for variable in {0..9}
do
  ./pccm g-10-30.txt "$variable" > out.txt
  diff out.txt "g-10-30-$variable.out" -w
  echo "Test $variable passed"
done
