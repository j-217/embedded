#!/bin/bash

U_NAME="ADMIN"
U_PASSWD="Tesing123"

while true
do
    echo "LOGIN"
    echo "-------------"
    read -p "Username: " INP_U_NAME
    read -s -p "Password: " INP_U_PASSWD
    echo
    echo "-------------"

    if [[ ! ${INP_U_NAME} || ! ${INP_U_PASSWD} ]]
    then
        echo "INPUT SOMETHING"
    elif [[ ${INP_U_NAME} = ${U_NAME} && ${INP_U_PASSWD} = ${U_PASSWD} ]]
    then
        echo "LOGGED IN!"
        exit
    else
        echo "WRONG USERNAME OR PASSWORD"
    fi
done