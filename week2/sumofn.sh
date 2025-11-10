#!/bin/bash

echo "enter n"
read n
sum=0
for (( i=0; i<=n; i++ ));
do
sum=$((sum + i))
done
echo "sum is $sum"
