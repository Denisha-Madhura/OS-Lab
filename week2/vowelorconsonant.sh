#!/bin/bash

echo "enter a single alphabet:"
read ch

case "$ch" in
    [aeiouAEIOU])
        echo "$ch is a vowel."
        ;;
    [a-zA-Z])
        echo "$ch is a consonant."
        ;;
    *)
        echo "invalid input"
        ;;
esac