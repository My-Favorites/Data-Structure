List Reverse(List L) {
    struct Node *cursor = L->Next;
    struct Node *next;
    struct Node *prev = NULL;
    while (cursor) {
        next = cursor->Next;
        cursor->Next = prev;
        prev = cursor;
        cursor = next;
    }
    L->Next = prev;
    return L;
}
