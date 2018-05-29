#!/bin/bash

dir=$1
cd $dir

complexity -t0 -s1 *.c > .comp.txt 2>.err.txt
cat .comp.txt

total=0
top=0
max=0
#get number of function
funcs=$(wc -l < ".comp.txt")
((funcs=funcs-3))
#find top quartile
quart=$((funcs / 4))
if [ $((funcs % 4)) -ne 0 ]; then
   ((quart=quart+1))
fi
#number of functions to skip before counting top funcs
((quart=funcs-quart))


#removes first 2 and last line and loops
while read -a line
do
   total=$(($total+${line[0]}))
   max=${line[0]}
   if [[ $quart < 1 ]]
   then
      top=$(($top+${line[0]}))
   else
      ((quart=quart-1))
   fi
done < <(tail -n +3 .comp.txt | head -n -1)

echo "Complexity Score: $total"
echo "Maximum Function Score: $max"
echo "Average Score: $(bc -l <<< "scale=2; $total/$funcs")"
echo "Ratio of top 25% to total: $(bc -l <<< "scale=2; $top/$total")"
echo ""
cat .err.txt

rm .comp.txt
rm .err.txt
