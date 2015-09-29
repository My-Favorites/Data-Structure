Stack CreateStack(int MaxElements)
{
	Stack stack = malloc(sizeof(*stack));
	stack->Capacity = MaxElements;
	stack->Top1 = 0;
	stack->Top2 = MaxElements - 1;
	stack->Array = malloc(sizeof(ElementType) * MaxElements);
	return stack;
}
int IsEmpty(Stack S, int Stacknum)
{
	if (Stacknum == 1)
	{
		return S->Top1 == 0;
	}
	else
	{
		return S->Top2 == S->Capacity - 1;
	}
}
int IsFull(Stack S)
{
	return S->Top1 > S->Top2;
}
int Push(ElementType X, Stack S, int Stacknum)
{
	if (S->Top1 > S->Top2)
	{
		return 0;
	}
	if (Stacknum == 1)
	{
		S->Array[S->Top1++] = X;	
	}
	else
	{
		S->Array[S->Top2--] = X;
	}
	return 1;
}
ElementType Top_Pop(Stack S, int Stacknum)
{
	if (Stacknum == 1)
	{
		if (S->Top1 == 0)
		{
			return ERROR;
		}
		return S->Array[--S->Top1];
	}
	else
	{
		if (S->Top2 == S->Capacity - 1)
		{
			return ERROR;
		}
		return S->Array[++S->Top2];
	}
}
