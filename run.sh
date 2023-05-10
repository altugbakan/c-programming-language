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
# if chapter 7, exercise 1
elif [ $1 -eq 7 ] && [ $2 -eq 1 ]
then
    if [ $# -lt 3 ]
    then
        echo "For Chapter 7, Exercise 1, the usage is" \
        "$0 <chapter-num> <exercise-num> <upper|lower>"
        exit 1
    fi
    
    EXECNAME=$3
fi

# if no EXECNAME, set it to FILENAME
if [ -z $EXECNAME ]
then
    EXECNAME=$FILENAME
fi

# compile the c file, run it, and delete the executable
cc -o $EXECNAME.out $FILENAME.c $LIBS
./$EXECNAME.out "${@:3}"
rm $EXECNAME.out
