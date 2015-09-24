/*
 * 功能：原地反转链表
 *
 * 作者：孙明琦
 *
 * 直接提交函数片段即可
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */

List Reverse(List L)
{
    struct Node* head = L;
    struct Node* curr = L->Next;
    struct Node* node = NULL;

    while (curr && curr->Next)
    {
        struct Node* next = curr->Next;
        curr->Next = node;
        node = curr;
        curr = next;
    }
    if (curr)
    {
        curr->Next = node;
    }
    head->Next = curr;

    return head;
}
