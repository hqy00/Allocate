#include "SeqList.h"
#include<assert.h>
#include<string.h>


void InitSeqList(SeqList* seq)	// ��ʼ��˳���
{
	assert(seq);
	memset(seq->array,0,sizeof(seq->array));
	seq->size = 0;

}


void PushBack(SeqList* pSeq, DataType data)// ��˳����β������ֵΪdata��Ԫ��
{
	assert(pSeq);
	if(pSeq->size >MaxSize)//�����ʱ��Ҫע���Ƿ�����
	{
		return;
	}
	else
	{
		pSeq->array[pSeq->size] = data;
		pSeq->size++;
	}

}


void PopBack(SeqList* pSeq)// ɾ��˳�������һ��Ԫ��
{
	assert(pSeq);
	if(0==pSeq->size)	//ɾ����ʱ��Ҫ�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		pSeq->size--;
	}

}

void PushFront(SeqList* pSeq, DataType data)// ��˳����ͷ������ֵΪdata��Ԫ��
{
	assert(pSeq);
	int i =0;
	if(pSeq->size >MaxSize)
	{
		return;
	}
	else
	{
		for(i=pSeq->size-1;i>=0;i--)
		{
			pSeq->array[i+1] = pSeq->array[i];
		}
		pSeq->array[0] = data;
		pSeq->size++;

	}
}


void PopFront(SeqList* pSeq)// ɾ��˳���ͷ��Ԫ��
{
	assert(pSeq);
	int i =0;
	if(0==pSeq->size)	
	{
		return;
	}
	else
	{
		for(i =0;i<pSeq->size-1;i++)
		{
			pSeq->array[i] = pSeq->array[i+1];
		}
		pSeq->size--;

	}

}


void Insert(SeqList* pSeq, int pos, DataType data)// ��˳�����posλ���ϲ���ֵΪdata��Ԫ��
{
	assert(pSeq);
	int i =0;
	if(pos > pSeq->size)            //�������������ݵ�����λ�ò��루��ͷ����β�����м����⴦��
	{
		return;
	}
	if(pSeq->size >MaxSize)
	{
		return;
	}
	else
	{
		for(i =pSeq->size-1;i>=pos;i--)
		{
			pSeq->array[i+1] = pSeq->array[i];
		}
		pSeq->array[pos] = data;
		pSeq->size++;

	}

}

void Erase(SeqList* pSeq, size_t pos)// ɾ��˳�����posλ���ϵ�Ԫ��
{
	assert(pSeq);
	int i =0;
	if(0==pSeq->size)	
	{
		return;
	}
	else
	{
		for(i=pos;i<pSeq->size-1;i++)
		{
			pSeq->array[i] = pSeq->array[i+1];
		}
		pSeq->size--;

	}


}

int Find(SeqList* pSeq, DataType data)// ��˳����в���ֵΪdata��Ԫ�أ��ҵ����ظ�Ԫ�ص�λ�ã����򷵻�-1
{
	assert(pSeq);
	int i =0;
	for(;i<pSeq->size;i++)
	{
		if(data == pSeq->array[i])
		{
			return i;
		}
	}

	return -1;
}


void PrintSeqList(SeqList* pSeq)    //��ӡ˳���
{
	assert(pSeq);
	int i =0;
	for(;i<pSeq->size;i++)
	{
		printf(" %d ",pSeq->array[i]);
	}

}

void Remove(SeqList* pSeq, DataType data)// ɾ��˳����е�һ��ֵΪdata��Ԫ��
{
	assert(pSeq);
	if( -1 == Find(pSeq,data))
	{
		return;
	}
	else
	{
		Erase(pSeq, Find(pSeq,data));
	}
}


void RemoveAll(SeqList* pSeq, DataType data)// ɾ��˳���������ֵΪdata��Ԫ��
{
	assert(pSeq);
	int i =0,count =0;
	for(;i<pSeq->size;i++)
	{
		if(data == pSeq->array[i])	//�Ƿ����data
		{
			count++;
		}
		else
		{
			pSeq->array[i-count] = pSeq->array[i];	//����count��
		}
	}
	pSeq->size -= count;
}



void BubbleSort(SeqList* pSeq)// ʹ��ð�������˳����е�Ԫ������
{
	int flag =0,i =0;
	for(;i<pSeq->size-1;i++)
	{
		int j =0;
		for(;j<pSeq->size-i-1;j++)
		{
			if(pSeq->array[j]>pSeq->array[j+1])	//����
			{
				int tmp = pSeq->array[j];
				pSeq->array[j] = pSeq->array[j+1];
				pSeq->array[j+1] = tmp;
				flag =1;
			}
			
		}

		if(0==flag)
		{
			return;
		}

	}

}


void SelectSort(SeqList* pSeq)// ʹ��ѡ�������˳����е�Ԫ������
{
	int begin =0,end =pSeq->size-1;
	int minpos =0,maxpos =end;
	int i =0;
	while(begin < end)
	{
		minpos =begin;
		maxpos =end;
		for(i=begin;i<=end;i++)
		{
			if(pSeq->array[i] > pSeq->array[maxpos])
			{
				maxpos = i;
			}
			if(pSeq->array[i] < pSeq->array[minpos])
			{
				minpos = i;
			}
		}

		//�������
		if(minpos != end && maxpos == begin)	//��Сλ����β�������λ���ײ�	
		{
			int p1 =pSeq->array[minpos];
			pSeq->array[minpos] = pSeq->array[begin];
			pSeq->array[begin] = p1;

			int p2 =pSeq->array[minpos];
			pSeq->array[minpos] = pSeq->array[end];
			pSeq->array[end] = p2;
		}
			
		if(maxpos != begin && minpos == end)	//���λ�����ײ�����Сλ��β��
		{
			int q1 =pSeq->array[maxpos];
			pSeq->array[maxpos] = pSeq->array[end];
			pSeq->array[end] = q1;

			int q2 =pSeq->array[maxpos];
			pSeq->array[maxpos] = pSeq->array[begin];
			pSeq->array[begin] = q2;
		}


		if(minpos != end && maxpos != begin)		//��Сλ����β�������λ�����ײ�
		{
			int temp1 =pSeq->array[minpos];
			pSeq->array[minpos] = pSeq->array[begin];
			pSeq->array[begin] = temp1;

			int temp2 =pSeq->array[maxpos];
			pSeq->array[maxpos] = pSeq->array[end];
			pSeq->array[end] = temp2;
		}

			if(minpos == end && maxpos ==begin)		//��Сλ��β�������λ���ײ�
		{
			int tmp3 =pSeq->array[minpos];
			pSeq->array[minpos] = pSeq->array[maxpos];
			pSeq->array[maxpos] = tmp3;

		}

		begin++;
		end--;

	}
}






int BinarySearch(SeqList* pSeq, DataType data)// ʹ�ö��ֲ�����˳����в���ֵΪdata
{
	int left =0,right =0,mid =0;
	left =0;						//�ؼ�Ҫ������������������ֵ�Ƿ���ȡ��
	right =pSeq->size-1;
	while(left <= right)
	{
		mid = left + ((right-left)>>1);
		if(data == pSeq->array[mid])
		{
			return mid;
		}
		else if(pSeq->array[mid] < data)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return 0;
}











int DG_BinarySearch(SeqList* pSeq, DataType data,int left,int right)// �ݹ�ʵ�ֶ��ֲ���
{
	int mid;
	if(left > right)
	{
		return 0;
	}
	mid = left + ((right - left)>>1);
	if(data == pSeq->array[mid])
	{
		return mid;
	}
	else if(data > pSeq->array[mid])
	{
		DG_BinarySearch(pSeq,data,mid+1,right);
	}
	else
	{
		DG_BinarySearch(pSeq,data,left,mid-1);
	}

}








void DG_PrintSeqList(SeqList* pSeq,int p_size)    //�ݹ��ӡ˳���
{
	assert(pSeq);
	p_size--;
	if(p_size != 0)
	{
		DG_PrintSeqList(pSeq,p_size);
	}

	printf(" %d ",pSeq->array[p_size]);

}

//void DG_PrintSeqList(SeqList* pSeq)    //�ݹ��ӡ˳���
//{
//	assert(pSeq);
//	pSeq->size--;
//	if(pSeq->size != 0)
//	{
//		DG_PrintSeqList(pSeq);
//	}
//
//	printf(" %d ",pSeq->array[pSeq->size++]);
//
//}











void fun1()
{
	SeqList Sx; 
	InitSeqList(&Sx);
	PushBack(&Sx,3);
	PushBack(&Sx,7);
	PushBack(&Sx,11);
	PushBack(&Sx,19);
	PushBack(&Sx,23);
	PushBack(&Sx,37);
	PushBack(&Sx,40);
	PushBack(&Sx,55);
	//int ret = DG_BinarySearch(&Sx,11,0,Sx.size - 1);
	//printf("%d",ret);
	DG_PrintSeqList(&Sx,Sx.size);
	//SelectSort(&Sx);
	//int ret = BinarySearch(&Sx,18);
	//printf("%d",ret);
	//BubbleSort(&Sx);
	//RemoveAll(&Sx, 2);
	//Remove(&Sx, 2);
	//Find(&Sx, 2);
	//Find(&Sx, 5);
	//PrintSeqList(&Sx);
	//Insert(&Sx, 1,5);
	//Erase(&Sx,3);
	//Erase(&Sx,0);
	//PopBack(&Sx);
	//PopBack(&Sx);
	
}

//void fun2()
//{
//	SeqList Sx; 
//	InitSeqList(&Sx);
//	PushFront(&Sx,1);
//	PushFront(&Sx,2);
//	PushFront(&Sx,3);
//	PushFront(&Sx,4);
//	PopFront(&Sx);
//	PopFront(&Sx);
//}






int main()
{
	fun1();
	//fun2();
	return 0;
}