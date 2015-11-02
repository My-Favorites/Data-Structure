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
    if (!source || !target) { // If one of BST is NULL
        if (!source && !target) { // If both is NULL
            return 1;
        }
        return 0;
    }
    if (!compare(source->Left, target->Left) ||
        !compare(source->Right, target->Right) ||
        source->Element != source->Element) {
        return 0;
    }
    return 1;
}

BST source;
BST target;

int main() {
    int n;
    int l;
    int input;
    for (;;) {
        scanf("%d", &n);
        if (n == 0) break;
        scanf("%l", &l);
        printf("N: %d, L: %d", n, l);
        source = NULL;
        for (int i = 0; i < l; i++) {
            target = NULL;
            for (int j = 0; j < n; j++) {
                scanf("%d", &input);
                // Create BST based on current index and input
                insert(input, i == 0 ? source : target);
            }
            printf(compare(source, target) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
