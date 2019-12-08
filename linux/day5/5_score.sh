#!/bin/bash

echo -n "Input Score: "
read S

if ! [ $S -ge 0 -a $S -le 100 ]
then
    echo "ERROR: INCORRECT SCORE"
    exit
fi

if [ $S -ge 90 ]
then
    GRADE=A
elif [ $S -ge 80 ]
then
    GRADE=B
elif [ $S -ge 70 ]
then
    GRADE=C
elif [ $S -ge 60 ]
then
    GRADE=D
else
    GRADE=E
fi

case $GRADE in
    A)
        echo "EXCELLENT"
        ;;
    B)
        echo "GREAT"
        ;;
    C)
        echo "GOOD"
        ;;
    D)
        echo "TOO BAD"
        ;;
    *)
        echo "SO CLOSE"
        ;;
esac