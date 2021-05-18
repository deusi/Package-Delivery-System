#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8081
fi

SCENE=$1
if [ -z "$1" ]
then
    SCENE=scenes/two_customers.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

valgrind --leak-check=full ${ROOTDIR}-build/bin/web-app $PORT web $SCENE
