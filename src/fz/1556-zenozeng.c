Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial c = calloc(1, sizeof(struct Node));
    Polynomial head = c;

    a = a->Next;
    b = b->Next;

    while (a || b) {
        struct Node* next = calloc(1, sizeof(struct Node));

        if (a && b && (a->Exponent == b->Exponent)) {
            next->Coefficient = a->Coefficient + b->Coefficient;
            next->Exponent = a->Exponent;
            a = a->Next;
            b = b->Next;
            if (next->Coefficient == 0) {
                 continue;
            }
        } else {
            if (!a || (b && (b->Exponent > a->Exponent))) {
                next->Coefficient = b->Coefficient;
                next->Exponent = b->Exponent;
                b = b->Next;
            } else if (!b || (a && (a->Exponent > b->Exponent))) {
                next->Coefficient = a->Coefficient;
                next->Exponent = a->Exponent;
                a = a->Next;
            }
        }
        c->Next = next;
        c = next;
    }

    return head;
}
