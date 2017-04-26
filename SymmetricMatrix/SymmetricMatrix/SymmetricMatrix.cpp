//ʵ�ֶԳƾ����Լ�ѹ���洢
/*
��������i>=j,������i<j   (i,j�±궼��0��ʼ)
���ڶԳƾ�����a(i,j)=a(j,i)�������л�����������ʽ���ɵ�
��ô����Ȼ�����ǿ��Խ�����һ���Գƾ����������Ԫ�أ�������ͬ�����У�ѹ���洢��һ��һԪ�����У�
�Ӷ���ʡ�϶�Ŀռ䣬���������Ƿ���һ����δ洢�� 
��������һ����һ��Ԫ�أ��ڶ���������Ԫ�ء�����i����i��Ԫ�ء��� 
���Գƾ�����n*n�ģ���������Ҫһ������Ϊ1+2+��+n�����������δ洢ÿ��Ԫ�أ����ݵȲ�����ǰn��͹�ʽ�ã�
S(n) = n*(n+1)/2
��ʽ��ʾ������ǰn�У�������n�У���Ԫ�ظ���

�������±�ʱ������i,j�±��Ǵ�0��ʼ�ģ�
���ԣ�S(i) = i * (i+1)/2
��ʾ������ǰi�У���������i�У���Ԫ�ظ���

�ٿ�����(��i��)����Ԫ��ǰ��j��Ԫ��

���Դ����±��Ժ󣬶Գƾ������Ԫ����һά�����е�λ�ô���һһ��Ӧ�Ĺ�ϵ��
�����Ǵ洢 i >= j,  SymmetricMatrix[i][j] == arry[i*(i+1)/2+j]
�����Ǵ洢 i < j,   SymmetricMatrix[i][j] == arry[j*(j+1)/2+i]

����ĳ�������ֻ���������ǡ�
*/

#include<iostream>
using namespace std;

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(int* a, size_t n)//����Ĺ���
		:_pData(new T[n*(n+1)/2])//Ϊѹ���洢��һά��������ռ�
		,_n(n)
	{
		size_t count = 0;
		for(size_t i=0; i<_n; i++)
		{
			for(size_t j=0; j < _n; j++)
			{
				if(i >= j)//��������
				{
					_pData[count] = a[i*n +j];
					count++;
				}
				else//�Ż���ֻҪi<j(������������)�Ͱ���������
				{
					break;
				}
			} 
		}
	}

	T& Access(int rows, int cols)
	{
		if(rows < cols)//������������
		{
			std::swap(rows,cols);//ת��������
		}
		
		return  _pData[rows*(rows+1)/2 +cols];

	}
        
	const T& Access(int rows, int cols)const
	{
		if(rows < cols)
		{
			std::swap(rows,cols);
		}
		
		return  _pData[rows*(rows+1)/2 +cols];
	}


	~SymmetricMatrix()//����
	{
		if(_pData)
		{
			delete[] _pData;
			_pData = NULL;
			_n = 0;
		}
	}

private:
	template<class TT>//��Ϊ����Ԫ��������ĳ�Ա���������������ģ�������Ҫ��ֻ���Լ����¶���
	friend ostream& operator<<(ostream& out,SymmetricMatrix<TT>& sm)//��<<�����������
	{
		for(size_t i=0; i< sm._n; i++)
		{
			for(size_t j=0; j < sm._n; j++)
			{
				out<<sm.Access(i,j)<<" ";

			}
			out<<endl;
		}

		return out;
	}

private:
	T* _pData;	//ѹ���洢��һά����
	size_t _n;	//n*n�ľ��� 
};


int main()
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },  
        { 1, 0, 1, 2, 3 },  
        { 2, 1, 0, 1, 2 },  
        { 3, 2, 1, 0, 1 },  
        { 4, 3, 2, 1, 0 }
	};


/*��ά���鰴��˳��洢���ڴ��еģ���һ�д�����Ŵ�ڶ��У��ڶ��д�����Ŵ�����С�������
���ݶ�ά�������ڴ��еĴ洢��ʽ�����Խ���ά���鿴��һά���鴦��
���Խ���ά����ǿת��һ��ָ�룬����һ��ָ�������ά���������Ԫ�ء�*/	
	SymmetricMatrix<int>sm((int*)a,5);
	cout<<sm<<endl;


	return 0;
}