#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include<stdio.h>


// ʵ��˳�������½ӿ�
typedef int DataType; //������������
#define MaxSize 10
#define NULL 0

typedef struct SeqList
{
	DataType array[MaxSize];
	int size;   // ��Ч����Ԫ�صĸ���
}SeqList;


void InitSeqList(SeqList* seq);	// ��ʼ��˳���

void PushBack(SeqList* pSeq, DataType data);// ��˳����β������ֵΪdata��Ԫ��

void PopBack(SeqList* pSeq);// ɾ��˳�������һ��Ԫ��

void PushFront(SeqList* pSeq, DataType data);// ��˳����ͷ������ֵΪdata��Ԫ��

void PopFront(SeqList* pSeq);// ɾ��˳���ͷ��Ԫ��

void Insert(SeqList* pSeq, size_t pos, DataType data);// ��˳�����posλ���ϲ���ֵΪdata��Ԫ��

void Erase(SeqList* pSeq, size_t pos);// ɾ��˳�����posλ���ϵ�Ԫ��

int Find(SeqList* pSeq, DataType data);// ��˳����в���ֵΪdata��Ԫ�أ��ҵ����ظ�Ԫ�ص�λ�ã����򷵻�-1

void PrintSeqList(SeqList* pSeq);    //��ӡ˳���

void DG_PrintSeqList(SeqList* pSeq,int p_size);    //�ݹ��ӡ˳���

void Remove(SeqList* pSeq, DataType data);// ɾ��˳����е�һ��ֵΪdata��Ԫ��

void RemoveAll(SeqList* pSeq, DataType data);// ɾ��˳���������ֵΪdata��Ԫ��

void BubbleSort(SeqList* pSeq);// ʹ��ð�������˳����е�Ԫ������

void SelectSort(SeqList* pSeq);// ʹ��ѡ�������˳����е�Ԫ������

int BinarySearch(SeqList* pSeq, DataType data);// ʹ�ö��ֲ�����˳����в���ֵΪdata

int DG_BinarySearch(SeqList* pSeq, DataType data,int left,int right)// �ݹ�ʵ�ֶ��ֲ���




#endif 










