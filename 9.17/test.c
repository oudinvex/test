#include <stdio.h>
#include <stdlib.h>


typedef struct _Node
{
	char data;

	struct _Node* lchild;
	struct _Node* rchild;
	struct _Node* parent;	
} Node, *BT;
BT create()
{
	char c;

	c = getchar();
	
	if(c == ' ') return NULL;	

	Node* root = malloc(sizeof(Node));
	root->data = c;
	root->lchild = create();
	root->rchild = create();

	return root;	
}
void first(BT t)
{
	if(t == NULL)
	{
	printf("*");
 return;
}
	printf("%c", t->data);
	first(t->lchild);
	first(t->rchild);
}
int main()
{
	BT t1;
	t1 = create();
	first(t1);
	return 0;
}
