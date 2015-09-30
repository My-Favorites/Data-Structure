#!/bin/bash

# Bash Script for Testing

echo ">> O(n^6)"
gcc on6.c test.c -std=c99 -o a.out
./a.out

echo ">> O(n^4)"
gcc on4.c test.c -std=c99 -o a.out
./a.out

echo ">> Bonus O(n^3)"
gcc bonus1.c test.c -std=c99 -o a.out
./a.out
