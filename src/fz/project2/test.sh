#!/bin/bash

gcc binary-search-tree.c -o bst.out
EXPECT=$(cat stdout)
RESULT=$(cat stdin | ./bst.out)
echo $EXPECT
echo $RESULT
[ "$EXPECT" == "$RESULT" ] && echo "All tests passed." || echo "Tests failed."
