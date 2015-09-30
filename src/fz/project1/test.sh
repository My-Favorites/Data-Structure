#!/bin/bash

# Bash Script for Testing

function testCode {
    echo # print an empty line
    echo -n ">> $1"
    gcc $2 test.c -std=c99 -o a.out
    ./a.out
}

testCode "O(n^6)" on6.c
testCode "O(n^4)" on4.c
testCode "Bonus O(n^3)" bonus1.c
