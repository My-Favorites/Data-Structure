/*���ߣ�������
 *
 *���ܣ�ԭ�ط�ת����
 *
 *ֱ���ύ����Ƭ�μ���
 */

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	int Element;
	Position Next;
};

/*Լ���������һ���ڵ�Ϊ�ڱ��ڵ㣬����Я�������������*/

List Reverse(List L)
{
	struct Node* head = L;
	struct Node* curr = L->Next;
	struct Node* node = NULL;
	while(curr && curr->Next)
	{
		struct Node* next = curr->Next;
		curr->Next = node;
		node = curr;
		curr = next;
	}
	if(curr)
	{
		curr->Next = node;
	}
	head->Next = curr;
	return head;
}
	