/*功能：合并两个用链表表示的多项式
 *
 *作者：孙明琦
 *
 *代码片段，直接提交函数部分即可
 */

typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

/*题目约定：链表的第一个节点为哨兵节点，并不储存有意义的数据*/

Polynomial Add(Polynomial a, Polynomial b)
{
	Polynomial result = calloc(1, sizeof(struct Node));
	Polynomial head = result;
	a = a->Next;
	b = b->Next;
	while (1)
	{
		if (a == 0 && b == 0)
		{
			return head;
		}
		else if (a == 0 || b == 0)
		{
			struct Node* nodeRemain;
			if (a == NULL)
			{
				nodeRemain = b;
			}
			else
			{
				nodeRemain = a;
			}
			result->Next = nodeRemain;
			a = NULL;
			b = NULL;
		}
		else
		{
			while (a && b && a->Exponent > b->Exponent)
			{
				struct Node* nodePrev = a;
				a = a->Next;
				result->Next = nodePrev;
				result = result->Next;
				result->Next = NULL;
			}
			while (a && b && b->Exponent > a->Exponent)
			{
				struct Node* nodePrev = b;
				b = b->Next;
				result->Next = nodePrev;
				result = result->Next;
				result->Next = NULL;
			}
			while (a && b && a->Exponent == b->Exponent)
			{
				if (a->Coefficient + b->Coefficient != 0)
				{
					struct Node* newNode = calloc(1, sizeof(struct Node));
					newNode[0] = b[0];
					newNode->Coefficient += a->Coefficient;
					newNode->Next = NULL;
					result->Next = newNode;
					result = result->Next;
				}
				b = b->Next;
				a = a->Next;
			}
		}
	}
}