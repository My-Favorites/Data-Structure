/*
 * by スノル
 */
#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */

Deque CreateDeque()
{
    Deque deque = malloc(sizeof(*deque));

    deque->Front = deque->Rear = malloc(sizeof(*deque->Front));
    deque->Front->Next = deque->Front->Last = NULL;

    return deque;
}

int IsEmpty(Deque D)
{
    return D->Front == D->Rear;
}

int Push(ElementType X, Deque D)
{
    PtrToNode p = malloc(sizeof(*p));

    p->Element = X;
    p->Next = D->Front->Next;
    p->Last = D->Front;
    if (IsEmpty(D))
        D->Rear = p;
    else
        D->Front->Next->Last = p;
    D->Front->Next = p;

    return 1;
}

ElementType Pop(Deque D)
{
    PtrToNode p;
    ElementType x;

    if (IsEmpty(D))
        return ERROR;
    p = D->Front->Next;
    x = p->Element;
    D->Front->Next = p->Next;
    if (p->Next)
        p->Next->Last = D->Front;
    else
        D->Rear = D->Front;
    free(p);

    return x;
}

int Inject(ElementType X, Deque D)
{
    PtrToNode p = malloc(sizeof(*p));

    p->Element = X;
    p->Next = NULL;
    p->Last = D->Rear;
    D->Rear->Next = p;
    D->Rear = p;

    return 1;
}

ElementType Eject(Deque D)
{
    PtrToNode p;
    ElementType x;

    if (IsEmpty(D))
        return ERROR;
    p = D->Rear;
    x = p->Element;
    D->Rear = p->Last;
    D->Rear->Next = NULL;
    free(p);

    return x;
}

Operation GetOp()
{
    return push;
} /* details omitted */
void PrintDeque(Deque D)
{
    return;
} /* details omitted */
