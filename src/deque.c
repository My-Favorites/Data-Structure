Deque CreateDeque()
{
    Deque deque = malloc(sizeof(*deque));
    struct Node* node = malloc(sizeof(*node));
    node->Next = NULL;
    node->Last = NULL;
    deque->Front = node;
    deque->Rear = node;
    return deque;
}
int Push(ElementType X, Deque D)
{
    struct Node* node = malloc(sizeof(*node));
    struct Node* dummy = D->Front;
    struct Node* next = D->Front->Next;
    if (node == NULL)
    {
        return 0;
    }
    dummy->Next = node;
    node->Last = dummy;
    node->Next = next;
    node->Element = X;
    if (next)
    {
        next->Last = node;
    }
    else
    {
        D->Rear = node;
    }
    return 1;
}
ElementType Pop(Deque D)
{
    int tmp;
    struct Node* node;
    struct Node* dummy;
    struct Node* next;
    if (D->Front == D->Rear)
    {
        return ERROR;
    }
    dummy = D->Front;
    next = D->Front->Next->Next;
    node = D->Front->Next;
    tmp = node->Element;
    dummy->Next = next;
    if (next)
    {
        next->Last = dummy;
    }
    else
    {
        D->Rear = D->Front;
    }
    return tmp;
}
int Inject(ElementType X, Deque D)
{
    struct Node* node = malloc(sizeof(*node));
    struct Node* end = D->Rear;
    if (node == NULL)
    {
        return 0;
    }
    end->Next = node;
    node->Last = end;
    node->Next = NULL;
    node->Element = X;
    D->Rear = node;
    return 1;
}

ElementType Eject(Deque D)
{
    int tmp;
    struct Node* node;
    struct Node* end;
    if (D->Front == D->Rear)
    {
        return ERROR;
    }
    node = D->Rear;
    end = node->Last;
    end->Next = NULL;
    tmp = node->Element;
    D->Rear = end;
    free(node);
    return tmp;
}
