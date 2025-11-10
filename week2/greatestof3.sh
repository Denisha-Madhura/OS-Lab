#!/bin/bash

echo "enter number 1"
read a
echo "enter number 2"
read b
echo "enter number 3"   
read c

if [ $a -gt $b ] && [ $a -gt $c ]
then
    echo "$a is the greatest number"
elif [ $b -gt $a ] && [ $b -gt $c ]
then
    echo "$b is the greatest number"
else
    echo "$c is the greatest number"
fi