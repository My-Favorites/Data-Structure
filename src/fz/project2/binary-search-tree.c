#include <stdio.h>
#include <stdlib.h>

/**
 * Define the type of tree element
 */
typedef int ElementType;

/**
 * Define Binary Search Tree
 */
typedef struct TreeNode *BST;
struct TreeNode {
    ElementType Element;
    BST Left;
    BST Right;
};

/**
 * Recursively insert an element to an existing BST
 */
BST insert(int x, BST T) {
    if (T == NULL) {
        // If T doesn't exist, create a new one
        T = (BST) malloc(sizeof(struct TreeNode));
        // Assign element to the new tree
        T->Element = x;
        // Initialize the new tree's left and right branches
        T->Left = T->Right = NULL;
    } else if (x < T->Element) {
        // If x is less than T's element, insert it to T's left branch
        T->Left = insert(x, T->Left);
    } else if (x > T->Element) {
        // If x is greater than T's element, insert it to T's right branch
        T->Right = insert(x, T->Right);
    }
    // if x is equal to T's element, do nothing and return
    return T;
}

/**
 * Recursively compare to see if two trees are identical
 */
int compare(BST source, BST target) {
    if (!source || !target) { // If one of BST is NULL
        return !source && !target; // If both are NULL, return true, else false
    }
    return source->Element == target->Element && // If both trees' root has same element
           compare(source->Left, target->Left) && // and both trees' left branch are identical
           compare(source->Right, target->Right); // and both trees' right branch are identical
}

int main() {
    // n: length of sequence, l: number of sequences
    int n, l;
    // input: each number of input sequence,
    // i,j: loop index
    int input, i, j;
    // Two binary search trees that will be compared
    BST source, target;

    // Infinite loop
    for (; ;) {
        scanf("%d", &n);
        if (n == 0) break;
        scanf("%d", &l);
        source = NULL;
        for (i = 0; i <= l; i++) {
            target = NULL;
            // Create a BST based on input
            for (j = 0; j < n; j++) {
                scanf("%d", &input);
                target = insert(input, target);
            }
            if (i == 0) {
                source = target;
            } else {
                // Print result
                printf(compare(source, target) ? "Yes\n" : "No\n");
            }
        }
    }

    // Safely exit
    return 0;
}
