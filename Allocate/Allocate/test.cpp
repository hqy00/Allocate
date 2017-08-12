//���Ժ���
#include<vector>  
using namespace std;
#include "SimpleAlloc.hpp"
  
void TestAlloc()  
{  
    vector<int*> v;  
    SimpleAlloc<int>sa;  
    for (size_t i = 0; i < 20; ++i)  
    {  
        __TRACE_DEBUG("�����ڴ��%d��\n",i+1);  
        v.push_back((int*)sa.Allocate());  
    }  
  
    int* p = (int*)sa.Allocate();  
  
    int i = 1;  
    while (!v.empty())  
    {  
        __TRACE_DEBUG("�ͷ��ڴ��%d��\n", i++);  
          
		int* ptm = v.back();  
		v.pop_back();  
        sa.Deallocate(ptm);  
    }  
  
    sa.Deallocate(p);  
}  

int main()
{
	TestAlloc();
	return 0;
}