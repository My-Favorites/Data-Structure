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

int compare(BST source, BST target) {
    return 0;
}

BST source;
BST current;

int main() {
    int n;
    int l;
    int input;
    for (;;) {
        scanf("%d", &n);
        if (n == 0) break;
        scanf("%l", &l);
        source = NULL;
        for (int i = 0; i < l; i++) {
            current = NULL;
            for (int j = 0; j < n; j++) {
                scanf("%d", &input);
                // Create BST based on current index and input
                insert(input, i == 0 ? source : current);
            }
            compare(source, target);
        }
    }
    printf("Hello, World!");
    return 0;
}
