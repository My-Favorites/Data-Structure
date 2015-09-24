#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
    int Coefficient;
    int Exponent;
    struct Node *Next;
};
typedef struct Node *Polynomial;

Polynomial Read()
{
    int n, i;
    Polynomial t, s = NULL;
   
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        t = malloc(sizeof(struct Node));
        t->Next = s;
        scanf("%d%d", &t->Coefficient, &t->Exponent);
        s = t;
    }

    return s;
}

void Print(Polynomial p)
{
    if (p == NULL)
        return;
    Print(p->Next);
    if (p->Next != NULL)
        printf(" ");
    printf("%d %d", p->Coefficient, p->Exponent);
}

Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial s = NULL, t, h = NULL;

    while (!(a==NULL||b==NULL)) {
        t = malloc(sizeof(struct Node));
        if (a->Exponent == b->Exponent) {
            t->Exponent = a->Exponent;
            t->Coefficient = a->Coefficient + b->Coefficient;
            a = a->Next;
            b = b->Next;
        } else if (a->Exponent < b->Exponent) {
            memcpy(t, a, sizeof(struct Node));
            a = a->Next;
        } else {
            memcpy(t, b, sizeof(struct Node));
            b = b->Next;
        }
        if (t->Coefficient == 0) {
            free(t);
            continue;
        }
        if (h != NULL)
            h->Next = t;
        else
            s = t;
        h = t;
    }
    while (a!=NULL) {
        t = malloc(sizeof(struct Node));
        memcpy(t, a, sizeof(struct Node));
        a = a->Next;
        if (h != NULL)
            h->Next = t;
        else
            s = t;
        h = t;
    
    }
    while (b!=NULL) {
        t = malloc(sizeof(struct Node));
        memcpy(t, b, sizeof(struct Node));
        b = b->Next;
        if (h != NULL)
            h->Next = t;
        else
            s = t;
        h = t;    
    }
    if (h == NULL)
        return NULL;
    h->Next = NULL;
    return s;
}

int main()
{
    Polynomial a, b, s;
    
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    printf("\n");

    return 0;
}

