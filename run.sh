#!/bin/bash

# if argument count is less than 2
if [ $# -lt 2 ]
then
    echo "Usage: $0 <chapter-num> <exercise-num>"
    exit 1
fi

# if exercise number is less than 10, add a 0 to the front
if [ $2 -lt 10 ]
then
    FILENAME="chapter-$1/exercise-0$2"
else
    FILENAME="chapter-$1/exercise-$2"
fi

# check special cases
# if chapter 4, exercise 5
if [ $1 -eq 4 ] && [ $2 -eq 5 ]
then
    LIBS="-lm"
fi

# compile the c file, run it, and delete the executable
cc -o $FILENAME.out $FILENAME.c $LIBS
./$FILENAME.out "${@:3}"
rm $FILENAME.out