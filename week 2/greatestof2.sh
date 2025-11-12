#!/bin/bash

echo "enter number 1"
read a
echo "enter number 2"
read b

if [ $a -gt $b ];
then
echo "$a is greatest"
else 
echo "$b is greatest"
fi  
