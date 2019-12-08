#!/bin/bash

if ! [ $1 ]
then
    echo "ERROR: INPUT A PARAM"
    exit
fi

if [ $1 ]
then
    if [ -e $1 ]
    then
        chmod 444 $1
        echo "$1 mode changed"
        exit
    else
        if [ -e tmp ]
        then
            cd tmp
        else
            mkdir tmp
            cd tmp
        fi
        touch $1
        echo "$1 created"
    fi
fi