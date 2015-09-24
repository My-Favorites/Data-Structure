/*作者：孙明琦
 *
 *功能：原地反转链表
 *
 *直接提交函数片段即可
 */

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	int Element;
	Position Next;
};

/*约定：链表第一个节点为哨兵节点，并不携带有意义的数据*/

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
	