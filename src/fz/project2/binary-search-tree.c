#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *BST;

BST insert(int x, BST T);

struct TreeNode {
    ElementType Element;
    BST Left;
    BST Right;
};

BST insert(int x, BST T) {
    if (T == NULL) {
        T = (BST) malloc(sizeof(struct TreeNode));
        T->Element = x;
        T->Left = T->Right = NULL;
    } else if (x < T->Element) {
        T->Left = insert(x, T->Left);
    } else if (x > T->Element) {
        T->Right = insert(x, T->Right);
    }
    return T;
}

int main() {
    printf("Hello, World!");
    return 0;
}
