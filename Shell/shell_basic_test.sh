#!/bin/bash

function my_add ()
{
    return $(($1 + $2))
}

function my_multiply ()
{
    return $(($1 * $2))
}

var1=1
var2=2

#var3=$[$var1 + $var2]
var3=`expr $var1 + $var2`

echo $var3

exit

read -p "Enter the first value: " var1
read -p "Enter the second value: " var2

my_add ${var1} ${var2}
echo $?

my_multiply ${var1} ${var2}
echo $?

i=1
num=$(($i+1))
echo $num

# ()
(
    #var3=`date`
    var3=$(date)
    echo ${var3}
) | grep "2017"

#(())
#var4=$(($var1 + $var2))
#var4=$[$var1 + $var2]
#var4=`expr $var1 \* $var2`
#var4=`echo "$var1 * $var2" | bc`
#echo ${var4}