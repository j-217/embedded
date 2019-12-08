#!/bin/bash

if ! [[ $1 ]]
then
    echo "ERROR: INPUT A PARAM"
    exit
fi

if [[ -d $1 ]]
then
    echo "$1 is a DIRECTORY file"
    exit
fi

if [[ -c $1 ]]
then
    echo "$1 is a CHARACTER file"
    exit
fi

if [[ -b $1 ]]
then
    echo "$1 is a BLOCK file"
    exit
fi

if [[ -p $1 ]]
then
    echo "$1 is a PIPE file"
    exit
fi

if [[ -S $1 ]]
then
    echo "$1 is a SOCKET file"
    exit
fi

if [[ -L $1 ]]
then
    echo "$1 is a LINK file"
    exit
fi

if [[ -f $1 ]]
then
    echo "$1 is a NOMAL file"
    exit
fi