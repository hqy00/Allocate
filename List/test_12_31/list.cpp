#include "list.h"



//��ʼ����������һ��ͷ��㣬����ʲôҲû����
//���㴴�����������¾���Ϊÿһ���ڵ����ռ䲢�ҳ�ʼ�������� 


//��ʼ��һ��û��ͷ���ĵ�����
void InitList(PNode* pHead)
{
	assert(pHead);
	*pHead = NULL;

}



// ������β������ֵΪdata���½��
void PushBack(PNode* pHead, DataType data)
{
	assert(pHead);
	if(NULL == *pHead)
	{
		*pHead = (PNode)malloc(sizeof(Node));
		(*pHead)->data = data;
		(*pHead)->next = NULL;
	}
	else
	{

		PNode NewNode,tag;							
		NewNode = (PNode)malloc(sizeof(Node));		//�����½��
		NewNode->data = data;		
		NewNode->next = NULL;
		tag = *pHead;
		while(tag->next)
		{
			tag = tag->next;
		}
		tag->next = NewNode;

	}

}


// ɾ����������һ���ڵ�
void PopBack(PNode* pHead)
{
	assert(pHead);
	PNode ppre,pcur;
	ppre = *pHead;
	pcur = ppre->next;
	if(NULL == *pHead)
	{
		return;
	}

	if(NULL == (*pHead)->next)
	{
		free(*pHead);
		*pHead = NULL;

	}
	else
	{
		while(pcur->next)
		{
			ppre = pcur;
			pcur = pcur->next;
		}
		free(pcur);
		ppre->next = NULL;
	}

}


// ������ͷ��������Ϊdata���½ڵ�
void PushFront(PNode* pHead, DataType data)
{
	assert(pHead);
	PNode NewNode;							
	NewNode = (PNode)malloc(sizeof(Node));		//�����½��
	NewNode->data = data;	
	if(NewNode->data == NULL)
	{
		return;
	}
	NewNode->next = *pHead;
	*pHead = NewNode;

}


// ɾ������ĵ�һ�����
void PopFront(PNode* pHead)
{
	assert(pHead);
	PNode ppre,pcur;
	ppre = *pHead;
	pcur = ppre->next;
	if(NULL == *pHead)
	{
		return;
	}
	*pHead = pcur;
	free(ppre);

}


// ����������ֵΪdata�Ľ�㣬���ڷ��ظý��ĵ�ַ�����򷵻ؿ�
PNode Find(PNode Head, DataType data)
{
	assert(Head);
	PNode tag;
	tag = Head;
	while(tag)
	{
		if(data == tag->data)
		{
			return tag;
		}
		tag = tag->next;
	}
	return NULL;

}


//������posλ�ú����ֵΪdata���½ڵ�
void Insert(PNode* pHead,PNode pos, DataType data)
{
	assert(pHead);
	PNode ppre,pcur,NewNode;							
	ppre = *pHead;
	pcur = ppre->next;
	NewNode = (PNode)malloc(sizeof(Node));		//�����½��
	NewNode->data = data;
	while(ppre!=pos)
	{
		ppre = pcur;
		pcur = pcur->next;
	}
	ppre->next = NewNode;
	NewNode->next = pcur;


}

// ɾ��������posλ���ϵĽ��
void Erase(PNode* pHead, PNode pos)
{
	assert(pHead);
	if(NULL == *pHead || NULL == pos)
	{
		return;
	}
	if(pos == *pHead)
	{
		(*pHead) = pos->next;
		free(pos);
	}
	else
	{
		PNode ppre,pcur;							
		ppre = *pHead;
		pcur = ppre->next;
		while(pcur!=pos)
		{
			ppre = pcur;
			pcur = pcur->next;
		}
		ppre->next = pos->next;
		free(pos);
	}


}


// �Ƴ������е�һ��ֵΪdata�Ľ��
void Remove(PNode* pHead, DataType data)
{
	assert(pHead);
	PNode Head,pos,tag;
	Head = *pHead;
	tag = *pHead;
	pos = Find(Head,data);
	if(NULL == *pHead || NULL == pos)
	{
		return;
	}
	if(pos == *pHead)
	{
		(*pHead) = pos->next;
		free(pos);
	}
	else
	{
		while(tag->next != pos)
		{
			tag = tag->next;
		}
		tag->next = pos->next;
		free(pos);

	}


}


// �Ƴ�����������ֵΪdata�Ľ��
void RemoveAll(PNode* pHead, DataType data)
{
	assert(pHead);
	PNode ppre,pcur;
	while(NULL != Find(*pHead,data))
	{
		ppre = *pHead;
		pcur = ppre->next;
		if(NULL == *pHead)
		{
			return;
		}
		if(data == ppre->data)
		{
			*pHead = pcur;
			free(ppre);
		}
		else
		{
			while(pcur->data != data)
			{
				ppre = pcur;
				pcur = pcur->next;
			}
			ppre->next = pcur->next;
			free(pcur);

		}
	}

}

// ��ȡ�����н����ܸ���
size_t Size(PNode pHead)
{
	assert(pHead);
	size_t count = 0;
	PNode tag = pHead;
	while(tag)
	{
		tag = tag->next;
		count++;
	}
	return count;

}

// ��ȡ�����е�һ�����
PNode Front(PNode pHead)
{
	assert(pHead);
	if(NULL == pHead)
	{
		return NULL;
	}
	else
		return pHead;

}


// ��ȡ���������һ���ڵ�
PNode Back(PNode pHead)
{
	assert(pHead);
	PNode tag;
	tag = pHead;
	if(NULL == tag)
	{
		return NULL;
	}
	else
	{
		while(tag->next)
		{
			tag = tag->next;
		}
		return tag;

	}

}

// �ж������Ƿ�Ϊ��
int Empty(PNode pHead)
{
	assert(pHead);
	if(NULL == pHead)
	{
		return -1;
	}
	else
	{
		return 1;
	}

}

// ��ӡ������
void PrintList(PNode pHead)
{
	assert(pHead);
	PNode tag;
	tag = pHead;
	if(NULL == tag)
	{
		return;
	}
	else
	{
		while(tag)
		{
			printf("%3d",tag->data);
			tag = tag->next;
		}

	}
}

// �����½ڵ�
PNode BuyNode(DataType data)
{
	PNode NewNode;							
	NewNode = (PNode)malloc(sizeof(Node));	
	NewNode->data = data;
	return NewNode;
}

// ��β��ͷ��ӡ������,���õݹ�ķ�����
void PrintListFromTail2Head(PNode pHead)
{
	PNode tag;
	tag = pHead;
	if(NULL == tag)
	{
		return;
	}
	else
	{
		PrintListFromTail2Head(tag->next);
		printf("%3d",tag->data);
	}

}


// ɾ����ͷ������ķ�β��㣬Ҫ�󣺲��ܱ���������
void DeleteNotTailNode(PNode* pHead,PNode pos)
{
	//�����滻��
	assert(pHead);
	PNode tag;
	if(NULL == pos->next || NULL == pos || NULL == *pHead)
	{
		return;
	}
	tag = pos->next;
	pos->data = tag->data;
	pos->next = tag->next;
	free(tag);

}


// ����ͷ�������ͷ���ǰ�����½ڵ�
void InsertNotHeadNode(PNode* pHead,PNode pos, DataType data)
{
	assert(pHead);
	PNode tag,NewNode;
	tag = pos->next;
	if(*pHead == pos || NULL == pos || NULL == *pHead)
	{
		return;
	}						
	NewNode = (PNode)malloc(sizeof(Node));	
	NewNode->data = pos->data;
	pos->next = NewNode;
	NewNode->next = tag;
	pos->data = data;

}


// �õ�����ʵ��Լɪ��
PNode JosephCircle(PNode *pHead, size_t M)
{
	assert(pHead);
	PNode back,ppre,pcur;
	if(NULL == *pHead)
	{
		return NULL;
	}
	back = Back(*pHead);
	back->next = *pHead;
	ppre = *pHead;
	pcur = ppre->next;
	while(ppre != ppre->next)
	{
		int tmp = M;
		while(--tmp)
		{	
			ppre = pcur;
			pcur = pcur->next;
		}
		//���滻��ɾ��
		ppre->data = pcur->data;
		ppre->next = pcur->next;
		free(pcur);
		pcur =ppre->next;
	}
	ppre->next = NULL;
	return ppre;

}



// ���õ�����--����ָ��
PNode ReverseList(PNode pHead)
{
	assert(pHead);
	PNode ppre,pcur,pnext;
	ppre = pHead;
	pcur = ppre->next;
	pnext = pcur->next;
	if(NULL == pHead->next)
	{
		return pHead;
	}
	else
	{
		while(pnext)
		{
			pcur->next = ppre;
			ppre = pcur;
			pcur = pnext;
			pnext = pnext->next;
		}
		pcur->next = ppre;
		pHead->next = pnext;	//���������Ժ�����һ���ڵ�
		pHead = pcur;			//����ͷ���ָ��pHead

	}

	return pHead;

}


// ���õ�����--ͷ�巨
PNode ReverseList_P(PNode pHead)
{
	assert(pHead);
	PNode pNewhead,pcur;
	pNewhead = NULL;
	pcur = pHead->next;
	if(NULL == pHead->next)
	{
		return pHead;
	}
	else
	{
		while(pcur)
		{
			pHead->next = pNewhead;
			pNewhead = pHead;
			pHead = pcur;
			pcur = pcur->next;
		}
		pHead->next = pNewhead;
		pNewhead = pHead;
	}

	return pHead;

}




// �Ե��������ð������--����
void BubbleSort(PNode pHead)
{
	assert(pHead);
	PNode ppre,pcur,ptail;
	ppre = pHead;
	pcur = ppre->next;
	ptail = NULL;
	if(NULL == pHead->next)
	{
		return;
	}
	else
	{
		while(pHead->next != ptail)
		{
			ppre = pHead;
			pcur = ppre->next;
			while(pcur != ptail)
			{
				if(ppre->data > pcur->data)
				{
					int tmp = ppre->data;
					ppre->data = pcur->data;
					pcur->data = tmp;
				}
				ppre = pcur;
				pcur = pcur->next;
			}
			ptail = ppre;
		}

	}

}



// ���ҵ�������м��㣬Ҫ��ֻ�ܹ�����һ������
PNode FindMidNode(PNode pHead)
{
	assert(pHead);
	PNode p1,p2;	//��p1һ����һ����p2һ��������
	p1 = pHead;
	p2 = pHead;
	while(NULL != p2 && NULL != p2->next)
	{
		p1 = p1->next;
		p2 = p2->next->next;
	}

	return p1;

}


// ���ҵ�����ĵ�����K����㣬ֻ�ܹ�����һ������
PNode FindLastKNode(PNode pHead, size_t K)
{
	assert(pHead);
	PNode p1,p2;	//����p2��k������p1,p2һ���ߣ�һֱ�ߵ�p2ΪNULL
	p1 = pHead;
	p2 = pHead;
	size_t count = Size(pHead);
	if(K > count || K<=0)
	{
		return NULL;
	}
	else
	{
		while(K--)
		{
			p2 = p2->next;
		}
		while(p2)
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
}

// ���ҵ�����ĵ�����K����㣬ֻ�ܹ�����һ������
PNode FindLastK2Node(PNode pHead, size_t K)
{
	assert(pHead);
	PNode p1,p2;	//����p2��k-1������p1,p2һ���ߣ�һֱ�ߵ�p2->nextΪNULL
	p1 = pHead;
	p2 = pHead;
	size_t count = Size(pHead);
	if(K > count || K<=0)
	{
		return NULL;
	}
	else
	{
		while(--K)
		{
			p2 = p2->next;
		}
		while(p2->next)
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
}

// ɾ��������ĵ�����K�����
PNode DeleteLastKNode(PNode * pHead, size_t K)
{
	assert(pHead);
	PNode pos,tag;
	pos = FindLastKNode(*pHead,K);
	if(NULL == pos)
	{
		return NULL;
	}
	if(pos == *pHead)
	{
		*pHead = (*pHead)->next;
		free(pos);
	}
	else
	{
		tag = pos->next;
		pos->data = tag->data;
		pos->next = tag->next;
		free(tag);
	}
	return *pHead;


}

// �ϲ��������������ϲ�֮����Ȼ����
PNode MergeList(PNode * pHead1, PNode * pHead2)
{
	assert(pHead1);
	assert(pHead2);
	PNode p1,p2,pNewhead,tag1,tag2;
	p1 = *pHead1;
	p2 = *pHead2;
	pNewhead = NULL;
	if(NULL == p1 || NULL == p2)
	{
		return NULL;
	}

	while(p1 && p2)
	{
		if(p1->data <= p2->data)
		{
			tag1 = p1->next;
			p1->next = pNewhead;
			pNewhead = p1;
			p1 = tag1;
		}
		else
		{
			tag2 = p2->next;
			p2->next = pNewhead;
			pNewhead = p2;
			p2 = tag2;
		}

	}
	if(NULL == p1 && NULL != p2)	//��ʱp1���ˣ�p2û��
	{
		while(p2)
		{
			tag2 = p2->next;
			p2->next = pNewhead;
			pNewhead = p2;
			p2 = tag2;
		}
	}
	if(NULL == p2 && NULL != p1)	//��ʱp2���ˣ�p1û��
	{
		while(p1)
		{
			tag1 = p1->next;
			p1->next = pNewhead;
			pNewhead = p1;
			p1 = tag1;
		}
	}

	return pNewhead;

}

//�ж����������Ƿ��ཻ
int IsListCross(PNode pHead1, PNode pHead2)
{
	PNode PTail1 = pHead1;
	PNode PTail2 = pHead2;
	if(NULL == pHead1|| NULL == pHead2)
	{
		return 0;
	}

	while(PTail1)
	{
		PTail1 = PTail1->next;
	}
	while(PTail2)
	{
		PTail2 = PTail2->next;
	}

	if(PTail1 == PTail2)
		return 1;

return 0;

}


//���������ཻ���󽻵�
PNode GetCrossNode(PNode pHead1, PNode pHead2)
{
	size_t count1 = 0;
	size_t count2 = 0;
	int gap = 0;//��ֵ
	PNode PL1 = pHead1;
	PNode PL2 = pHead2;
	if(0 == IsListCross(pHead1,pHead2))
	{
		return NULL;
	}
	count1 = Size(pHead1);
	count2 = Size(pHead2);
	gap = count1 - count2;
	if(gap > 0)
	{
		while(gap--)
		{
			PL1 = PL1->next;
		}
	}
	else
	{
		gap = 0 - gap;
		while(gap--)
		{
			PL2 = PL2->next;
		}
	}

	while(PL1 != PL2)
	{
		PL1 = PL1->next;
		PL2 = PL2->next;
	}

	return PL1;


}
//�ж������Ƿ����,�����Ļ�����������
PNode HasCircle(PNode pHead)
{
	PNode PFast = pHead;
	PNode PSolw = pHead;

	while(PFast && PFast->next)
	{
		PFast = PFast->next->next;
		PSolw = PSolw->next;
		if(PFast == PSolw)
		{
			return PFast;
		}
	}

	return NULL;
}
//�󻷵ĳ���
size_t GetCircleLen(PNode pMeetNode)
{
	PNode pCurNode = pMeetNode;
	size_t count = 0;
	if(NULL == pMeetNode)
	{
		return 0;
	}

	while(pCurNode->next != pMeetNode)
	{
		count++;
		pCurNode = pCurNode->next;

	}
	count += 1;//������pMeetNode����

	return count;
}

//�󻷵���ڵ�
PNode GetEnterNode(PNode pHead,PNode pMeetNode)
{
	PNode pH = pHead;//��һ��ָ��ͷ����ָ��
	PNode pM = pMeetNode;//��һ��ָ���������ָ��
	if(NULL == pHead || NULL == pMeetNode)
	{
		return NULL;
	}

	while(pH != pM)
	{
		pH = pH->next;
		pM = pM->next;
	}

	return pH;

}
//�ж����������Ƿ����
int HasCircleWithCircle(PNode pHead1,PNode pHead2)
{
	PNode pL1 = pHead1;
	PNode pL2 = pHead2;

	//�ж����������Ƿ����
	PNode pMeetNode1 = HasCircle(pHead1);
	PNode pMeetNode2 = HasCircle(pHead2);

	//����������
	if(NULL == pMeetNode1 && NULL == pMeetNode2)
	{
		while(pL1->next)
		{
			pL1 = pL1->next;
		}
		while(pL2->next)
		{
			pL2 = pL2->next;
		}
		//���β�����ͬ�����ཻ
		if(pL1 == pL2)
		{
			return 1;
		}

	}
	else if(pMeetNode1 && pMeetNode2)//������������,���ཻ��϶�pCurNode��һȦ������pMeetNode2
	{
		PNode pCurNode = pMeetNode1;
		while(pCurNode->next  != pMeetNode1)
		{
			if(pCurNode == pMeetNode2)
			{
				return 2;
			}
			pCurNode = pCurNode->next;
		}
		if(pCurNode == pMeetNode2)
		{
			return 2;
		}
	}

	return 0;

}


//��������ĸ���
PNode CopyComplexList(PNode pHead)
{
	PNode p1 = pHead;
	PNode p2 = NULL;
	PNode pNewNode = NULL;
	if(NULL == pHead)
	{
		return NULL;
	}

	//���ȣ���ԭ����ÿ�����֮�����һ���½��
	while(p1)
	{
		pNewNode = BuyNode(p1->data);
		assert(pNewNode);//�ж�pNewNode�Ƿ�Ϊ��
		pNewNode->next = p1->next;
		p1->next = pNewNode;
		p1 = p1->next->next;
	}

	//���ţ����½��������ֵ
	p1 = pHead;
	p2 = p1->next;
	while(p2->next)
	{
		if(NULL == p1->random)
		{
			p2->random = NULL;
		}
		else
		{			
			p2->random = p1->random->next;
		}
		p1 = p2->next;
		p2 = p1->next;
	}
	//����ѭ���������һ�����
	if(NULL == p1->random)
	{
		p2->random = NULL;
	}
	else
	{			
		p2->random = p1->random->next;
	}

	//���ԭ����
	p1 = pHead;
	p2 = p1->next;
	pNewNode  = p2;//�����������ͷ
	while(p2->next)
	{
		p1->next = p2->next;
		p2->next = p1->next->next;
		p1 = p1->next;
		p2 = p2->next;
	}
	p1->next = p2->next;

	return pNewNode;


}
void fun1()
{
	PNode head;
	InitList(&head);
	//PushBack(&head,1);
	//PushBack(&head,2);
	//PushBack(&head,3);
	//PushBack(&head,4);
	//PopBack(&head);
	//PopBack(&head);
	PushFront(&head,1);
	PushFront(&head,2);
	PushFront(&head,3);
	PushFront(&head,4);
	PopFront(&head);
	PopFront(&head);

}


void fun2()
{
	PNode head,ps;
	InitList(&head);	
	PushBack(&head,11);
	PushBack(&head,4);
	PushBack(&head,8);
	PushBack(&head,2);
	//PushBack(&head,3);
	//ps = head->next;
	//Insert(&head,ps,5);
	//ps = head;
	//Erase(&head, ps);
	//Remove(&head,2);
	//Remove(&head,1);
	//RemoveAll(&head,2);
	//Size(head);
	//Front(head);
	//Back(head);
	//Empty(head);
	//PrintList(head);
	//BueNode(10);
	//PrintListFromTail2Head(head);
	//DeleteNotTailNode(&head,ps);
	//InsertNotHeadNode(&head,ps,5);
	//ps = JosephCircle(&head, 3);
	//printf("%d",ps->data);
	//ps = ReverseList_P(head);
	//PrintList(ps);
	//BubbleSort(head);
	//PrintList(head);
	//ps = FindMidNode(head);
	//printf("%d",ps->data);
	//ps = FindLastKNode(head,3);
	//printf("%d",ps->data);
	//ps = FindLastK2Node(head,3);
	//printf("%d",ps->data);
	//ps = DeleteLastKNode(&head,3);
	//PrintList(ps);

}


void fun3()
{
	PNode head1,head2,ps;
	InitList(&head1);
	InitList(&head2);
	PushBack(&head1,8);
	PushBack(&head1,11);
	PushBack(&head1,21);
	PushBack(&head1,28);
	PushBack(&head2,4);
	PushBack(&head2,17);
	PushBack(&head2,32);
	PushBack(&head2,45);
	ps = MergeList(&head1,&head2);
	PrintList(ps);

}

void fun4()
{
	PNode head1,head2,ptail,ret;
	InitList(&head1);
	InitList(&head2);
	PushBack(&head1,1);
	PushBack(&head1,2);
	PushBack(&head1,3);
	PushBack(&head1,4);
	PushBack(&head1,5);
	PushBack(&head1,6);

	PushBack(&head2,4);
	PushBack(&head2,5);
	PushBack(&head2,6);

	ptail = Back(head2);//ʹ�������ཻ
	ptail->next = Find(head1,5);
	ret = GetCrossNode(head1,head2);
	printf("%d\n",ret->data);

}

void fun5()
{
	PNode head1,pTailNode,pMeetNode,pEnterNode;
	InitList(&head1);
	PushBack(&head1,1);
	PushBack(&head1,2);
	PushBack(&head1,3);
	PushBack(&head1,4);
	PushBack(&head1,5);
	PushBack(&head1,6);
	PushBack(&head1,7);
	PushBack(&head1,8);
	PushBack(&head1,9);

	pTailNode = Back(head1);//����
	pTailNode->next = Find(head1,5);

	pMeetNode = HasCircle(head1);
	if(NULL == pMeetNode)
	{
		printf("������\n");
	}
	else
	{
		printf("%d\n",GetCircleLen(pMeetNode));

	}

	pEnterNode = GetEnterNode(head1,pMeetNode);
	printf("%d\n",pEnterNode->data);
}

void fun6()
{
	PNode head1,head2,ptail1,ptail2;

	InitList(&head1);
	PushBack(&head1,1);
	PushBack(&head1,2);
	PushBack(&head1,3);
	PushBack(&head1,4);
	PushBack(&head1,5);
	PushBack(&head1,6);

	InitList(&head2);
	PushBack(&head2,4);
	PushBack(&head2,5);
	PushBack(&head2,6);

	//���컷���ཻ
	ptail1 = Back(head1);//��������1����
	ptail1->next = Find(head1,4);

	ptail2 = Back(head2);//��������2������1�����ཻ
	ptail2->next = Find(head1,2);

	printf("%d\n",HasCircleWithCircle(head1,head2));


}

void fun7()
{
	Node node1,node2,node3,node4,*pHead;
	node1.data = 1;
	node1.next = &node2;
	node1.random = &node3;

	node2.data = 2;
	node2.next = &node3;
	node2.random = &node2;

	node3.data = 3;
	node3.next = &node4;
	node3.random = NULL;

	node4.data = 4;
	node4.next = NULL;
	node4.random = &node2;

	pHead = CopyComplexList(&node1);
}

int main()
{
	//fun1();
	//fun2();
	//fun3();
	//fun4();
	//fun5();
	//fun6();
	fun7();
	return 0;
}