#!/bin/bash

echo "enter a file name"
read filename
if [ ! -f "$filename" ]; then
    echo "file does not exist"
    exit 1
fi
lineCount=$(wc -l < "$filename")
if [ "$lineCount" -lt 5 ];
then
    echo "file has less than 5 lines"
    exit 1
fi

echo "current file content:"
cat "$filename"
echo "enter new content to append to the file:"
read newContent
echo "$newContent" >> "$filename"
echo "updated file content:"
cat "$filename"