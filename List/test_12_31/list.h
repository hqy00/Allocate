#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//ʵ����ͷ����������²���
typedef int DataType;

typedef struct Node
{
	struct Node * next;
	struct Node * random;
	DataType data;
}Node,*PNode;



// ��ʼ��������---˼��ΪʲôҪ���ݶ���ָ��
void InitList(PNode* pHead);

// ������β������ֵΪdata���½��
void PushBack(PNode* pHead, DataType data);

// ɾ����������һ���ڵ�
void PopBack(PNode* pHead);

// ������ͷ��������Ϊdata���½ڵ�
void PushFront(PNode* pHead, DataType data);

// ɾ������ĵ�һ�����
void PopFront(PNode* pHead);

// ����������ֵΪdata�Ľ�㣬���ڷ��ظý��ĵ�ַ�����򷵻ؿ�
PNode Find(PNode Head, DataType data);

//������posλ�ú����ֵΪdata���½ڵ�
void Insert(PNode* pHead,PNode pos, DataType data);

// ɾ��������posλ���ϵĽ��
void Erase(PNode* pHead, PNode pos);

// �Ƴ������е�һ��ֵΪdata�Ľ��
void Remove(PNode* pHead, DataType data);

// �Ƴ�����������ֵΪdata�Ľ��
void RemoveAll(PNode* pHead, DataType data);

// ��ȡ�����н����ܸ���
size_t Size(PNode pHead);

// ��ȡ�����е�һ�����
PNode Front(PNode pHead);

// ��ȡ���������һ���ڵ�
PNode Back(PNode pHead);

// �ж������Ƿ�Ϊ��
int Empty(PNode pHead);

// ��ӡ������
void PrintList(PNode pHead);

// �����½ڵ�
PNode BuyNode(DataType data);

//////////////////����������////////////////////////////////////
// ��β��ͷ��ӡ������
void PrintListFromTail2Head(PNode pHead);

// ɾ����ͷ������ķ�β��㣬Ҫ�󣺲��ܱ���������
void DeleteNotTailNode(PNode pHead,PNode pos);

// ����ͷ�������ͷ���ǰ�����½ڵ�
void InsertNotHeadNode(PNode* pHead,PNode pos, DataType data);

// �õ�����ʵ��Լɪ��
PNode JosephCircle(PNode *pHead, size_t M);

// ���õ�����--����ָ��
PNode ReverseList(PNode pHead);

// ���õ�����--ͷ�巨
PNode ReverseList_P(PNode pHead);

// �Ե��������ð������--����
void BubbleSort(PNode pHead);

// ���ҵ�������м��㣬Ҫ��ֻ�ܹ�����һ������
PNode FindMidNode(PNode pHead);

// ���ҵ�����ĵ�����K����㣬ֻ�ܹ�����һ������
PNode FindLastKNode(PNode pHead, size_t K);

// ���ҵ�����ĵ�����K����㣬ֻ�ܹ�����һ������
PNode FindLastK2Node(PNode pHead, size_t K);

// ɾ��������ĵ�����K�����
PNode DeleteLastKNode(PNode * pHead, size_t K);

// �ϲ��������������ϲ�֮����Ȼ����
PNode MergeList(PNode * pHead1, PNode * pHead2);

//�ж����������Ƿ��ཻ
int IsListCross(PNode pHead1, PNode pHead2);

//���������ཻ���󽻵�
PNode GetCrossNode(PNode pHead1, PNode pHead2);

//�ж������Ƿ����
PNode HasCircle(PNode pHead);

//�󻷵ĳ���
size_t GetCircleLen(PNode pMeetNode);

//�󻷵���ڵ�
PNode GetEnterNode(PNode pHead,PNode pMeetNode);

//�ж����������Ƿ����
int HasCircleWithCircle(PNode pHead1,PNode pHead2);

//��������ĸ���
PNode CopyComplexList(PNode pHead);

#endif