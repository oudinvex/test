#include"SeqList.h"
#include<stdio.h>
#include<stdlib.h>
//2. 初始化
void InitSequenceList(seqlist* slist)
{
	slist->size = 0;
}
//3. 尾部插入值为x的节点
void InsertInSequenceListTail(seqlist* slist, datatype x)
{
	if (slist->size == MAX_SIZE)
	{
		printf("the sequence list is full!\n");
		exit(1);
	}
	slist->a[slist->size]=x;
	slist->size++;
}
//4. 打印各节点的值
void PintSequenceList(seqlist* slist)
{
	if (!IsSequenceListEmpty(slist))
		printf("The list is empty!\n");
	else
		for (int i = 0; i < slist->size; i++)
			printf("%d", slist->a[i]);
}
//5. 判断顺序表是否为空
int IsSequenceListEmpty(seqlist* slist)
{
	return slist->size == 0 ? 0 : 1;
}
//6. 查找值为x的节点的位置
int SearchNumInSequenceListPos(seqlist* slist, datatype x)
{
	int i = 0;
	while (slist->a[i] != x&&i < slist->size)
		i++;
	return i < slist->size ? i : -1;
}
//7. 取得第i个节点的值
datatype GetValueInSequenceListPos(seqlist* slist, int i)
{
	if (i<0 || i >= slist->size)
	{
		printf("The position dese not exist!\n"); exit(1);
	}
	else
		return slist->a[i];
}
//8.在i位置插入x值
void InsertInSequenceListPos(seqlist* slist,int pos,datatype x)
{
	if(slist->size==MAX_SIZE)
	{
		printf("\nThe list is full!\n");
		exit(1);
	}
	if(pos<0||pos>slist->size)
	{
		printf("\nThe position does not exist!");
		exit(1);
	}
	for (int i = slist->size; i > pos; i--)
		slist->a[i] = slist->a[i - 1];
	slist->a[pos] = x;
	slist->size++;
}
//9. 删除i位置的节点
void DeleteInSequenceListPos(seqlist* slist, int pos)
{
	if(pos<0||pos>=slist->size)
	{
		printf("The position does not exist!\n");
		exit(1);
	}
	for (int i = pos; i < slist->size - 1; i++)
		slist->a[i] = slist->a[i + 1];
	slist->size--;
}
