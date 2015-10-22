#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */
void PrintNode( Tree NodePtr )
{
   printf(" %d", NodePtr->Element);
}

void Level_order ( Tree T, void (*visit)(Tree ThisNode) );

int main()
{
    Tree T = BuildTree();
    printf("Level-order:");
    Level_order(T, PrintNode);
    return 0;
}

/* Your function will be put here */

Tree BuildTree()
{
    return (Tree)malloc(sizeof(struct TreeNode));
} /* details omitted */

void Level_order(Tree T, void (*visit)(Tree ThisNode))
{
    Tree queue[MaxTree];
    int head, tail;
    Tree u;

    if (!T)
        return;

    head = tail = 0;
    
    queue[tail++] = T;
    while (tail != head) {
        u = queue[head++];
        visit(u);
        if (u->Left)
            queue[tail++] = u->Left;
        if (u->Right)
            queue[tail++] = u->Right;
    }
}
