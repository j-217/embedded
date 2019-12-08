#!/bin/bash

echo -n "input two numbers: "
read X Y

echo "--Menu--"
echo " 1: add"
echo " 2: sub"
echo " 3: mul"
echo " 4: div"
echo -n "choose one operator: "

read Op

case $Op in
    1)
        R=`expr ${X} + ${Y}`
        ;;
    2)
        R=`expr ${X} - ${Y}`
        ;;
    3)
        R=`expr ${X} \* ${Y}`
        ;;
    4)
        R=`expr ${X} / ${Y}`
        ;;
    *)
        echo "Operator Error"
        ;;
esac

echo "result: ${R}"