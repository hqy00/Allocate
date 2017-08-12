#pragma once

//һ���ռ�������
#include<iostream>
using namespace std;
#include<memory.h>
#include<stdlib.h>
#include"trace.h"

typedef void(* NewHandleFunPtr) ();//����ָ������
template<int inst>
class MallocAllocTemplate
{

public:
	static void* Allocate(size_t n)//Allocate
	{
		void* result = malloc(n);
		if(result == NULL)
		{
			result = OOM_Malloc(n);
		}
		return result;
	}

	static void* Reallocate(void* p,size_t /*oldsize*/,size_t newsize)//Reallocate
	{
		void* result = realloc(p,newsize);
		if(result == NULL)
		{
			result = OOM_Realloc(p,newsize);
		}
		return result;
		
	}


	static NewHandleFunPtr SetHandleFun(NewHandleFunPtr f)//���ÿռ����벻��ʱ�Ĵ�����
	{
		NewHandleFunPtr old = NewHandleFun;
		NewHandleFun = f;
		return old;
	}

	static void* OOM_Malloc(size_t n)//malloc����ռ�ʧ��ʱ����OOM_Malloc��������
	{
		NewHandleFunPtr temp;
		for(;;)//���ϵ����ڴ治��ʱ�Ĵ�����
		{
			temp  = NewHandleFun;
			if(NULL == temp)
				throw std::bad_alloc();

			(*temp)();
			
			void* result = malloc(n);
			if(result)
				return result;
		}
	}

	static void* OOM_Realloc(void* p,size_t newsize)//realloc����ռ�ʧ��ʱ����OOM_Realloc��������
	{
		NewHandleFunPtr temp;
		for(;;)//���ϵ����ڴ治��ʱ�Ĵ�����
		{
			temp  = NewHandleFun;
			if(NULL == temp)
				throw std::bad_alloc();

			(*temp)();
			
			void* result = realloc(p,newsize);
			if(result)
				return result;
		}
	}

	static void Deallocate(void* p,size_t/* n*/)//Deallocate
	{
		free(p);
	}
private:
	static NewHandleFunPtr NewHandleFun;//���崦�����ĺ���ָ��
};

template<int inst>
NewHandleFunPtr MallocAllocTemplate<inst>::NewHandleFun = 0;







 //�����ռ�������

enum { ALIGN = 8}; //С������ϵ��߽�
enum { MAXTYPES = 128}; //С�����������
enum { NFREELISTS = MAXTYPES/ALIGN};//freelists�ĸ���16��

template<bool threads, int inst>
class DefaultAllocTemplate
{
private:
	//RoundUp��bytes�ϵ���8�ı���
	static size_t RoundUp(size_t bytes)
	{ 
		return ( ( bytes + ALIGN -1 ) & (~(ALIGN - 1)) );//�� a & 0x1000,�൱�ڽ�a�ĺ���λ��0���õ�����8�ı���
	}

private:
	union obj//free_list�Ľڵ㹹��
	{
		union obj* free_list_link;//�ŵ�����һ���ڴ��ĵ�ַ
		char client_data[1];//����ѿռ佻���û�����ŵ����û�����
	};

private:
	//16��free_lists
 	static obj* volatile free_list[NFREELISTS];//���16���������������

	//�����ֽڴ�С������ʹ�õ�n��free_list��n��0��ʼ��
	static size_t FreeIndex(size_t bytes)
	{
		return ((bytes + ALIGN - 1)/ALIGN-1);
	}

	//����һ����СΪn�ֽڵĶ��󣬲����ܼ����СΪn���������鵽free_list�Ķ�Ӧ����
	static void* Refill(size_t n);

	//����һ���ռ䣬������nobjs����СΪsize�ֽڵ����飬nobjsĬ��Ϊ20����
	//����һ�ڴ�ؿռ䲻�㣬��õ�����������С��20��
	static char* ChunkAlloc(size_t size,int &nobjs);

	/*chunkalloc�����ڱ���*/
	static char* startfree;	//�ڴ����ʼλ��
	static char* endfree;	//�ڴ�ؽ���λ��
	static size_t heapsize;	//��¼һ�������˶��ٿռ�

public:
	static void* Allocate(size_t n);
	static void  Deallocate(void* p,size_t n);
	static void* Reallocate(void* p,size_t oldsize,size_t newsize);
};

//������Ծ�̬��Ա������ʼ��
template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::startfree = 0;

template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::endfree = 0;

template<bool threads,int inst>
size_t DefaultAllocTemplate<threads,inst>::heapsize = 0;

template<bool threads,int inst>
typename DefaultAllocTemplate<threads,inst>::obj* volatile DefaultAllocTemplate<threads,inst>::free_list[NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

 


/***********************************����Ժ������ж���**************************************/

//Allocate�м�Ĺ��������������ͷɾ��ȡ��ͷ��㹩�û�ʹ�ã��ٸ���head��λ��
template<bool threads,int inst>
void* DefaultAllocTemplate<threads,inst>::Allocate(size_t n)
{
	__TRACE_DEBUG("�����ڴ�:%d\n", n); 
	obj* volatile * my_free_list;
	obj* result;

	//����128�͵���һ���ռ�������
	if( n > MAXTYPES )
	{
		return (MallocAllocTemplate<inst>::Allocate(n));
	}

	//Ѱ��16��free_lists�к��ʵ�һ��
	my_free_list = free_list + FreeIndex(n);
	result = *my_free_list;
	if(result == NULL)
	{
		//û�ҵ��ʺ��Լ����õ�free_lists��׼���������һ���ʺ��Լ��Ŀ��õ�free_lists
		void* r = Refill(RoundUp(n));
		 __TRACE_DEBUG("����������freeList[%d]ȡ�ڵ�\n", FreeIndex(n)); 
		return r;
	}
	//����free_lists
	*my_free_list = result->free_list_link;
	return result;
}



//Deallocate�м�Ĺ��������������ͷ�壬�ٸ���head��λ��
template<bool threads,int inst>
void DefaultAllocTemplate<threads,inst>::Deallocate(void *p, size_t n)
{
	__TRACE_DEBUG("�ͷ��ڴ�(p:%p, n: %u)\n", p, n);
	obj* volatile * my_free_list;
	obj* q = (obj*)p;

	//����128�͵���һ���ռ�������
	if( n > MAXTYPES )
	{
		MallocAllocTemplate<inst>::Deallocate(p,n);
		return;
	}

	//Ѱ��16��free_lists�к��ʵ�һ��
	my_free_list = free_list + FreeIndex(n);
	//����free_lists,��������
	q->free_list_link = *my_free_list;
	*my_free_list = q;
}


//����һ����СΪn�ֽڵĶ��󣬲����ܼ����СΪn�ֽڵ��������鵽free_list�Ķ�Ӧ����
//����n�Ѿ��ʵ�����8�ı�����ȱʡ�����Ĭ���������20�������飬����һ�ڴ�ؿռ䲻�㣬��õ�����������С��20��
template<bool threads,int inst>
void* DefaultAllocTemplate<threads,inst>::Refill(size_t n)
{
	int nobjs = 20;
	/*����ChunkAlloc����������ȡ��nobjs��������Ϊfree_lists���½�㣬�����ChunkAlloc
	�����е�nobjs���������ã���ΪChunkAlloc�����ڲ���������Ĳ�ͬ�����nobjs�����޸ģ�
	��Refill����Ҫͨ��nobjs��ֵ������Ӧ�Ĵ������Դ�������*/
	char* chunk = ChunkAlloc(n,nobjs);

	obj* volatile* my_free_list;
	obj* result;
	obj* current_obj;
	obj* next_obj;
	int i;

	//���ֻ��һ�����飬�ͽ���������������ã�free_lists���½��
	if(1 == nobjs)
		return chunk;

	//����׼������free_list�������½��
	my_free_list = free_list + FreeIndex(n);

	//��������chunk�ռ��ڽ���free_list

	result = (obj* ) chunk;//����һ������������
	*my_free_list = next_obj = (obj*)(chunk + n);
	
	//ѭ����1��ʼ����Ϊ��0�����������
	for(i = 1; ; i++)
	{
		current_obj = next_obj;
		next_obj = (obj*)((char*)next_obj + n);
		if(nobjs - 1 == i)
		{
			current_obj->free_list_link = 0;
			break;
		}
		else
			current_obj->free_list_link = next_obj;
	}
	return result;
}


//����size�Ѿ��ʵ�����8�ı�����ȱʡ�����Ĭ��nobjs�������20�������飬
//����һ�ڴ�ؿռ䲻�㣬��õ�����������С��20��
template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::ChunkAlloc(size_t size, int &nobjs)
{
	char* result;
	size_t totalbytes = size * nobjs;
	size_t bytesleft = endfree - startfree;//�ڴ��ʣ��ռ�

	if(bytesleft > totalbytes)
	{//�ڴ��ʣ��ռ���ȫ����������20������ 

		__TRACE_DEBUG("�ڴ�����㹻�Ŀռ����%d������\n",nobjs); 
		result = startfree;
		startfree += totalbytes;
		return result;
	}
	else if(bytesleft >= size)
	{//�ڴ�ؿռ䲻�㣬�������� 1 <= ���� <  20

		__TRACE_DEBUG("�ڴ��ֻ���Է���%d������\n", nobjs);
		nobjs = bytesleft/size;
		totalbytes = size * nobjs;
		result = startfree;
		startfree += totalbytes;
		return result;
	}
	else
	{//�ڴ��ʣ��ռ���һ�������С���޷��ṩ

		 __TRACE_DEBUG("�ڴ�ط��䲻��1������\n", nobjs);  
		size_t bytes_to_get = 2 * totalbytes + RoundUp(heapsize>>4);
		//�����������ڴ���е���ͷ�������ü�ֵ
		if(bytesleft > 0)
		{
			//�ڴ���л���ʣ����ͷ�ռ䣬����Ѱ�Һ��ʵ�free_list
			obj* volatile* my_free_list = free_list + FreeIndex(bytesleft);

			//����free_list,����ͷ�ռ����
			((obj* )startfree)->free_list_link = *my_free_list;
			*my_free_list = (obj* )startfree;

			__TRACE_DEBUG("�ڴ�ؽ�ʣ����ڴ����freeList[%d]��\n", FreeIndex(bytesleft)); 
		}


		//��ϵͳ��������һ���ڴ��
		startfree = (char*)malloc(bytes_to_get);
		__TRACE_DEBUG("��ϵͳ�л�ȡ%d�ڴ�\n", bytes_to_get);

		if(0 == startfree)
		{
			//ϵͳ�ռ䲻�㣬����ռ�ʧ��
			int i;
			obj* p;
			obj* volatile* my_free_list;
			//���ԴӴ��ڵ���size�ֽڵ�free_list�Ͻ�һ���������
			for(i = size;i < MAXTYPES;i += ALIGN)
			{
				my_free_list = free_list + FreeIndex(i);
				p = *my_free_list;
				if(NULL != p)//˵���п��Խ��õ��������
				{
					//����free_list���ó����õ�����
					*my_free_list = p->free_list_link;
					startfree = (char* )p;
					endfree = startfree + i;

					//�ݹ�����Լ���Ϊ������nobjs��ֵ
					return (ChunkAlloc(size,nobjs));
					//ע�⣬�κβ�����ͷ�ս��������ʵ���free_list�б���
				}
			}
			 //��ֹ��һ���Malloc�׳��쳣  
            __TRACE_DEBUG("���İ취��ȥһ���ռ��������н��в���\n"); 

			endfree = 0;

			//��ϵͳ�ڴ治�㣬�ұ��free_listҲû�п��õ������ܽ�
			//��ʱ��ֻ�ܳ��Ե���һ���ռ��������������ܷ񾡵���
			startfree = (char* )MallocAllocTemplate<inst>::Allocate(bytes_to_get);
		}

		heapsize += bytes_to_get;
		endfree = startfree + bytes_to_get;
		//�ݹ�����Լ���Ϊ������nobjs��ֵ
		return (ChunkAlloc(size,nobjs));
		
	}


}