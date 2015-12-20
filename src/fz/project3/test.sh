#!/bin/bash

g++ reconstruct.cpp -o a.out

test() {
    EXPECT=$(cat $2)
    RESULT=$(cat $1 | ./a.out)
    echo "STDIN:"
    cat $1
    echo ""
    echo "Expect: $EXPECT"
    echo "Result: $RESULT"
    [ "$EXPECT" == "$RESULT" ] && echo "Match: TRUE" || echo "Match: FALSE."
    echo ""
}

test stdin stdout
test stdin2 stdout2
test stdin3 stdout3
test stdin4 stdout4
test stdin5 stdout5



