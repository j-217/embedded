#!/bin/bash

# RAM_N=`expr \`date +%S\` % 10`
RAM_N=$(expr $(date +%S) % 10)

# echo ${RAM_N}
for((;;))
do
echo -n "GUESS THE NUMBER(0 - 9): "
read G

    if ! [ $G -ge 0 -a $G -le 9 ]
    then
        echo "INCORRECT NUMBER"
    elif [ $G -eq $RAM_N ]
    then
        echo "CONGRATULATIONS! THE NUMBER IS $G"
        break
    else
        echo "SORRY! WRONG NUMBER! TRY AGAIN"
    fi
done