#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct _code
{
	char data;
	struct _code* next1;
	struct _code* next2;
	struct _code* befor;
}code,*BT;

BT create()
{
	char c;
	c=getchar();
	if(c==' ') return NULL;
	code* root = (code*)malloc(sizeof(code));
	root->data = c;
	cout<<"success"<<endl;
	root->next1 = create();
	root->next2 = create();
	return root;
}

void first(BT t)
{
if(t==NULL) return;
printf("%c",t->data);
first(t->next1);
first(t->next2);
}




int main()
{
	BT a;
	a=create();
	//first(a);

	return 0;
}
