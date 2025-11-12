#!/bin/bash

echo "enter number"
read n
r=$((n%2))
if [ $r -eq 0 ];
then
echo "even number"
else
echo "odd number"
fi