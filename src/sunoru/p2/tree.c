#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
};
Tree insert(int x, Tree T);
int compare(Tree T1, Tree T2);
void dispose(Tree T);

int main()
{
    int n, l;
    Tree T1, T2;
    char ch;
    int i, j;
    int temp;

    T1 = T2 = NULL;
    for (;;) {
        scanf("%d", &n);
        if (n == 0)
            break;
        scanf("%d", &l);
        dispose(T1);
        T1 = NULL;
        for (i = 0; i < n; i++) {
            scanf("%d", &temp);
            T1 = insert(temp, T1);
        }
        for (j = 0; j < l; j++) {
            dispose(T2);
            T2 = NULL;
            for (i = 0; i < n; i++) {
                scanf("%d", &temp);
                T2 = insert(temp, T2);
            }
            if (compare(T1, T2)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }

    return 0; 
}

Tree insert(int x, Tree T)
{
    if (T == NULL) {
        T = (Tree) malloc(sizeof(struct TreeNode));
        if (T == NULL) {
            return;
        } else {
            T->Element = x;
            T->Left = T->Right = NULL;
        }
    } else if (x < T->Element) {
        T->Left = insert(x, T->Left);
    } else if (x > T->Element) {
        T->Right = insert(x, T->Right);
    }
 
    return T;
}

int compare(Tree T1, Tree T2)
{
    if ((!T1) || (!T2))
        return (!T1) && (!T2);
    if (T1->Element != T2->Element)
        return 0;

    return (compare(T1->Left, T2->Left) && compare(T2->Right, T1->Right));
}

void dispose(Tree T) {
    if (!T)
        return;
    dispose(T->Left);
    dispose(T->Right);
    free(T);
}
