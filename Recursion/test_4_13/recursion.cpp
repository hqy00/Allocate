//#include<iostream>
//using namespace std;

//�õݹ鷽ʽ������³���

//��ǰN����Ȼ��֮��
//int N_Sum(int n)
//{
//	if(n == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return N_Sum(n-1) + n;
//	}
//
//}
//int main()
//{
//	cout<<N_Sum(5)<<endl;
//	return 0;
//}


//��N�Ľ׳�
//int fac(int n)
//{
//	if(n == 1)
//	{
//		return 1;
//	}
//	else
//	{
//		return fac(n-1) * n;
//	}
//
//}
//int main()
//{
//	cout<<fac(5)<<endl;
//	return 0;
//}


//struct Node{
//
//	Node(int value)
//		:data(value)
//	{}
//
//	Node* next;
//	int data;
//};
//�����ӡ������
//void  PrintReverse(Node *&phead)
//{
//	if(phead)
//	{
//		PrintReverse(phead->next);
//		cout<<phead->data<<endl;
//	}
//}
//
//int main()
//{
//	Node(1),Node(2),Node(3),Node(4);
//	Node *a = &Node(1);
//	Node *b = &Node(2);
//	Node *c = &Node(3);
//	Node *d = &Node(4);
//
//	a->next  = b;
//	b->next  = c;
//	c->next  = d;
//	d->next  = NULL;
//
//	PrintReverse(&a);
//
//}

//�������ٵ�����
//void DestroyReserve(Node *&phead)
//{
//	if(phead)
//	{
//		DestroyReserve(phead->next);
//		delete phead;//ע��������deleteɾ�����ͱ�����new������㿪�ٿռ�
//		phead  = NULL;
//	}
//
//}
//
//int main()
//{
//	Node *a = new Node(1);
//	Node *b = new Node(2);
//	Node *c = new Node(3);
//	Node *d = new Node(4);
//
//	a->next  = b;
//	b->next  = c;
//	c->next  = d;
//	d->next  = NULL;
//
//	DestroyReserve(&a);
//}


//�ڵ��������������ĳ��ֵΪdata�Ľ��
//Node* Find(Node* phead,int data)
//{
//	if(phead)
//	{
//		Node* res = Find(phead->next,data);//res�������ǰ��ҵ��Ľ�㷵��ȥ
//		if(res)
//		{
//			return res;
//		}
//		else
//		{
//			if(data == phead->data)
//			{
//				return phead;
//			}
//		}
//	}
//
//	return NULL;
//}
//
//int main()
//{
//	Node *a = new Node(1);
//	Node *b = new Node(2);
//	Node *c = new Node(3);
//	Node *d = new Node(4);
//
//	a->next  = b;
//	b->next  = c;
//	c->next  = d;
//	d->next  = NULL;
//
//	if(Find(a,2))
//	{
//		cout<<"�ҵ���\n"<<endl;
//	}
//}

//���ֲ��ҵݹ���ʽ
//int BinarySearch(int* array,int left,int right,int data)
//{
//	if(left > right)//�Ϸ��Լ��
//	{
//		return;
//	}
//	int mid = left + (right - left)>>1;
//	if(data == array[mid])
//	{
//		return array[mid];
//	}
//	else if(data < array[mid])
//	{
//		return BinarySearch(array,left,mid,data);
//	}
//	else
//	{
//		return BinarySearch(array,mid+1,right,data);
//	}
//
//	return -1;
//}

//�����ӡ�����е�Ԫ��
//void PrintfReverseArray(int* arr,int size)
//{
//	if(size)
//	{
//		cout<<arr[size-1]<<" ";//����������ӡ���ȴ�ӡ�ٵݹ飬����Ϊ����һ��ʼ�����ҵ����һ��Ԫ�أ���������
//		PrintfReverseArray(arr,size-1);
//	}
//
//}
//
//int main()
//{
//	int arr[] = {1,2,3,4,5};
//	PrintfReverseArray(arr,5);
//	return 0;
//}


//�ж�һ���ַ����Ƿ�Ϊ����
//��ͨ��
//bool Ispalindereme(char* str,size_t size)
//{
//	int begin = 0;
//	int end = size -1;
//	while(begin < end)//���������������ַ�������ѭ����������bagin = end;����ż���������ַ�������ѭ����������bagin > end;
//	{
//		if(str[begin] != str[end])
//		{
//			return false;
//		}
//		begin++;
//		end--;
//	}
//
//	return true;
//}

//�ݹ��
//bool Ispalindereme(char* str,size_t size)
//{
//	if(size <= 1)
//		return true;
//	if(str[0] != str[size-1])//�Ż��ˣ����ж���β�Ƿ�һ��
//	{
//		return false;
//	}
//	return Ispalindereme(str+1,size-2);
//	return true;
//
//}

//ȫ����Perm����������ʱ�临�Ӷ�
//void Perm(int* arr,int size,int N)
//{
//	if(size == N)
//	{
//		for(size_t idx;idx < size;idx++)
//		{
//			cout<< arr[idx]<<"";
//		}
//		
//		cout<<endl;
//	}
//	else
//	{
//		for(size_t idx = N;idx < size;idx++)
//		{
//			std::swap(arr[i],arr[N]);
//			Perm(arr,size,N+1);
//			std::swap(arr[i],arr[N]);
//		}
//	}
//}
//
//��ʱ�临�Ӷ�ΪN��
//




