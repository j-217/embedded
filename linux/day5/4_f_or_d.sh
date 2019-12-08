#!/bin/bash

if ! [[ $1 ]]
then
    echo "ERROR: INPUT A PARAM"
    exit
fi

if [[ -d $1 ]]
then
    echo "$1 is a DIR file"
    ls -l | more
    exit
elif [[ -f $1 ]]
then
    echo "$1 is a NOMAL file"
    cat $1 | more
    exit
else
    echo "$1 is other file"
    exit
fi