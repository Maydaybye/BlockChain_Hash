  #include<stdio.h>
#include<stdlib.h>

#define REMAINDER 11	// 通常是质数

typedef struct element
{
	int key;
	int value;
	
}Element;

typedef struct Pnode
{
	Element* data;
	struct Pnode* next;
}Node;

typedef struct hash_table
{
	int size;
	int length;
	struct Pnode* head;
}Hash_table;


int hash(int value)
{
	return value % REMAINDER;
}

Hash_table* Creat_Table(int table_size)
{
	Hash_table* h = (Hash_table*)malloc(sizeof(Hash_table));
	h->size = REMAINDER;
	h->head = (Node*)malloc((h->size) * sizeof(Node));
	h->length = 0;
	int i = 0;
	for (i = 0; i < h->size; i++)
	{
		h->head[i].next = NULL;
	}
	return h;
}

Node* lookup(Hash_table* h, int key)
{
	int i;
	i = hash(key);
	Node* p = h->head[i].next;
	while (p && key != p->data->key)
	{
		p = p->next;
	}

	return p;
}

void Insert(Hash_table* h, Element k)
{
	Node* p = lookup(h, k.key);
	if (!p)
	{
		Node* q = (Node*)malloc(sizeof(Node));
		q->data = (Element*)malloc(sizeof(Element));
		(q->data)->key = k.key;
		(q->data)->value = k.value;
		int position;
		position =  hash(k.key);
		q->next = h->head[position].next;//头插新节点，尾节点指向NULL
		h->head[position].next = q;

		h->length += 1;
		return;
	}
	else
	{
		printf("The keys is exist !\n");
		return;
	}
}

void Destroy_Table(Hash_table* h)
{
	int i;
	Node* p, * q;
	for (i = 0; i < h->size; i++)
	{
		p = h->head[i].next;
		while (p)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
	free(h->head);
	free(h);
}

void print_Table(Hash_table* h)
{
	int i = 0;
	for (i = 0; i < h->size; i++)
	{
		Node* p = h->head[i].next;
		while (p)
		{
			printf("[%d-%d] ", p->data->key, p->data->value);
			p = p->next;
		}
		printf("NULL\n");
	}
}

int main()
{
	Element a[] = { {12,1},{2,2},{31,3},{45,4},{8,5} };

	int n = sizeof(a) / sizeof(Element);
	Hash_table* h = Creat_Table(n);
	int i = 0;
	for (i = 0; i < n; i++)
	{
		Insert(h, a[i]);
	}
	print_Table(h);		// 打印哈希表 
	printf("%d\n\n", lookup(h, 31)->data->value);	//查找key值为12的Element  
	printf("%d\n", h->length);	//打印哈希表的元素个数 
	Destroy_Table(h);	// 摧毁哈希表 
	return 0;
}
