#ifndef SEQLIST_H
#define SEQLIST_H
/***************************************************
 * 顺序表结构定义及其实现
 * *****************************************************/
// 1. 顺序表结构
#define MAX_SIZE 100
typedef int datatype;
typedef struct tagSeqList {
	datatype a[MAX_SIZE];
	int size;//顺序表的元素个数
}seqlist;
//2. 初始化
void InitSequenceList(seqlist* slist);
//3. 尾部插入值为x的节点
void InsertInSequenceListTail(seqlist* slist,datatype x);
//4. 打印各节点的值
void PintSequenceList(seqlist* slist);
//5. 判断顺序表是否为空
int IsSequenceListEmpty(seqlist* slist);
//6. 查找值为x的节点的位置
int SearchNumInSequenceListPos(seqlist* slist, datatype x);
//7. 取得第i个节点的值
datatype GetValueInSequenceListPos(seqlist* slist, int i);
//8.在i位置插入x值
void InsertInSequenceListPos(seqlist* slist, int pos, datatype x);
//9. 删除i位置的节点
void DeleteInSequenceListPos(seqlist* slist, int pos);
#endif // SEQLIST_H
