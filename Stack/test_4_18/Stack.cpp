//*********************ʵ��Stack�Ļ�������***************************
//  Ҫ���ڽ�������ʱ���ȴ����¿ռ䣬�ٰ�ԭ�ռ�����ݿ������¿ռ䣬���ͷžɿռ䣬���ָ���¿ռ䡣
//	�ڰ�ԭ�ռ�����ݿ������¿ռ�ʱ�������������ַ�����1>ʹ��memcpy����Ԫ�أ�2>ʹ��forѭ����ֵ
//  memcpy�������ŵ���Ч�ʸߣ�ȱ��������ǳ������memcpy�����Ĺ����Ǵ�Դsrc��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n���ֽڵ�Ŀ��dest��ָ���ڴ��ַ����ʼλ����
//	forѭ���������ŵ��ǲ�����ǳ�������������ȱ����Ч�ʵ�
//	Ϊ�˿���ʱ������Ч�ʸߣ����ܹ˼���ǳ������������������������ȡ��
//	������ȡ�����ջ�б������POD��������������)�������������Ͳ��ÿ�����ǳ��������ôֱ��ʹ��memcpy����Ԫ��
//  ������POD��������������),��Ҫ������ǳ��������ʱʹ��forѭ�����п���
//#include<iostream>
//using namespace std;
//#include<assert.h>
//#include "date.h"
//
//
//struct _TrueType
//{
//	bool Get()
//	{
//		return true;
//	}
//};
//
//struct _FalseType
//{
//	bool Get()
//	{
//		return false;
//	}
//};
//
//template<class TP>
//struct TypeTraits	//���������͵���ģ����
//{
//	typedef _FalseType _IsPODType;
//};
//
////*************�������͵��������Ӧ��ģ������ػ�*****************
//template<>
//struct TypeTraits<int>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<unsigned int>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<char>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<unsigned char>
//{
//	typedef _TrueType _IsPODType;
//};
//
//
//template<>
//struct TypeTraits<short>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<unsigned short>
//{
//	typedef _TrueType _IsPODType;
//};
//
//
//template<>
//struct TypeTraits<long>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<unsigned long>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<double>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<long double>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<float>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<long long>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<unsigned long long>
//{
//	typedef _TrueType _IsPODType;
//};
//
//template<>
//struct TypeTraits<bool>
//{
//	typedef _TrueType _IsPODType;
//};
//
////*****************************************************************
//
////ջ��ʵ��
//template<class T>
//class Stack
//{
//public:
//	Stack(size_t capacity = 10)//����
//		:_size(0)
//		,_capacity(capacity)
//		,_pData(new T[capacity])
//	{}
//
//    Stack(const Stack<T>& s)//��������-->�ȴ���һ����sһģһ���Ŀռ�--->�ٽ�s�����ݿ�������������ȡ��
//		:_size(s._size)
//		,_capacity(s._capacity)
//		,_pData(new T[s._capacity])
//	{
//		cout<<"Type :"<<typeid(T).name<<endl;//��ӡջ�ڴ�����ݵ�����
//		if(TypeTraits<T>::_IsPODType().Get())
//		{
//			memcpy(_pData,s._pData,s._size * sizeof(T));
//		}
//		else
//		{
//			for(size_t idx = 0; idx < s._size;idx++)
//			{
//				_pData[idx] = s._pData[idx];
//			}
//		}
//	}
//
//    Stack<T>& operator=(const Stack<T>& s)//��ֵ���������
//	{
//		cout<<"Type :"<<typeid(T).name<<endl;
//
//		if(this != &s)
//		{
//			if(NULL != _pData)
//			{
//				delete[] _pData;//����ԭ�ռ�
//				_pData = new T[s._capacity];//�������¿��ٺ�sһ����С���¿ռ�
//				_capacity = s._capacity;
//			}
//		
//			if(TypeTraits<T>::_IsPODType().Get())//����������ȡ����s������ݿ������¿ռ�
//			{
//				memcpy(_pData,s._pData,s._size * sizeof(T));
//			}
//			else
//			{
//				for(size_t idx = 0; idx < s._size;idx++)
//				{
//					_pData[idx] = s._pData[idx];
//				}
//			}
//
//			_size = s._size;
//
//		}
//
//		return *this;
//	}
//
//	void Push(const T& num)//ѹջ
//	{
//		_CheckCapacity();//�ȼ��ջ������
//		_pData[_size] = num;
//		_size++;
//
//	}
//
//	void Pop()//��ջ
//	{
//		assert(0 != _size);
//		_size--;
//
//	}
//	size_t Size()const//ջ����ЧԪ�ظ���
//	{
//		return _size;
//	}
//
//	size_t Capacity()const//ջ��������С
//	{
//		return _capacity;
//	}
//
//	T& Top()//ջ��Ԫ��
//	{
//		return _pData[_size-1];
//	}
//
//	const T& Top()const
//	{
//		return _pData[size-1];
//
//	}
//
//	bool Empty()const//�ж�ջ�Ƿ�Ϊ��
//	{
//		return 0 == _size;
//	}
//	
//	~Stack()//����
//	{
//		if(_pData)
//		{
//			delete[] _pData;
//			_pData = NULL;
//			_size = 0;
//			_capacity = 0;
//
//		}
//
//	}
//
//	void Printf()
//	{
//		for(size_t idx = 0; idx < _size;idx++)
//		{
//			cout<<_pData[idx]<<" ";
//		}
//		cout<<endl;
//	}
//
//
//private:
//	T* _pData;		//ָ��ջ��ָ��
//	size_t _capacity;//ջ������
//	size_t _size;	//ջ������Ԫ�ظ���
//
//
//private:
//	void _CheckCapacity()//�����������������ʱ����
//	{
//		if(_size == _capacity)//��Ϊջ�Ľṹ�����ˣ���ֻ�ܶ�ջ����һ��Ԫ�ؽ��в������������ݳ��ֵ����ֻ����_size == _capacity
//		{
//			// ����ռ�
//			T* temp = new T[_capacity*2+3];//����һ��������Ϊ�˷�ֹ����ʱ������_capacity��0
//			
//			// ����Ԫ��
//			if(TypeTraits<T>::_IsPODType().Get())//����������ȡ����s������ݿ������¿ռ�
//			{
//				memcpy(temp,_pData,_size * sizeof(T));
//			}
//			else
//			{
//				for(size_t idx = 0; idx < _size;idx++)
//				{
//					temp[idx] = _pData[idx];
//				}
//			}
//
//			// �ͷžɿռ�
//			delete[] _pData;
//
//			// ָ���¿ռ�
//			_pData = temp;
//			_size = _size;
//			_capacity = _capacity * 2 + 3;
//
//		}
//	}
//
//
//};


//int main()
//{
//	Date d1(2017,3,3);
//	Date d2(2017,5,1);
//	Date d3(2017,4,25);
//	Stack<Date> s(1);//����������
//
//	s.Push(d1);
//	s.Push(d2);
//	s.Push(d3);
//
//	Stack<int> s1;//��������
//	Stack<int> s2(0);
//	Stack<int> s3(3);

	//s1.Push(1);
	//s1.Push(2);
	//s1.Push(3);
	//s1.Push(4);
	//s1.Printf();
	//s1.Pop();
	//s1.Printf();
	//cout<<s1.Top()<<endl;
	//cout<<s1.Size()<<endl;
	//cout<<s1.Capacity()<<endl;

	//s2.Push(1);
	//s2.Push(2);
	//s2.Push(3);
	//s2.Push(4);
	//s2.Printf();
	//s2.Pop();
	//s2.Printf();
	//cout<<s2.Top()<<endl;
	//cout<<s2.Size()<<endl;
	//cout<<s2.Capacity()<<endl;

//	return 0;
//}


//***********************���沨�����ʽ����׺���ʽ����������************************
//����׺���ʽת��Ϊ�沨�����ʽ����׺���ʽ�������ڼ����沨�����ʽ��ֵ��
//#include<iostream>
//#include<stack>
//using namespace std;
//#include<assert.h>
//
//enum OPERATOR //����ö������
//{
//	DATA,
//	ADD,
//	SUB,
//	MUL,
//	DIV
//};
//
//struct Cell //����Ԫ��
//{
//	OPERATOR _operator;//����ö�����͵ı���
//	int _data;//��ֵ
//};
//
//
//int CalcRpn(Cell cell[],size_t size)
//{
//	stack<int> s;//����ջs
//	for(size_t idx = 0;idx < size; idx++)
//	{
//		if(cell[idx]._operator == DATA)//��������־���ջ
//		{
//			s.push(cell[idx]._data);
//		}
//		else
//		{
//			int right = s.top();//���ȳ�ջ�����ݣ���Ϊ˫Ŀ���������Ҳ�����
//			s.pop();
//			int left = s.top();//�ú��ջ�����ݣ���Ϊ˫Ŀ���������������
//			s.pop();
//
//			switch(cell[idx]._operator)
//			{
//			case ADD:
//				s.push(left + right);
//				break;
//
//			case SUB:
//				s.push(left - right);
//				break;
//
//			case MUL:
//				s.push(left * right);
//				break;
//
//			case DIV:
//				if(right == 0)//�����ĳ�������Ϊ0
//				{
//					return -1;
//				}
//				s.push(left / right);
//				break;
//
//			default:
//				cout<<"����������ʽ�����޷�ʶ��Ĳ�����"<<endl;
//				exit(1);
//
//
//			}
//		}
//	}
//	return s.top();
//
//}
//int main()
//{
//	// 12 3 4 + * 6 - 8 2 / +  ���沨�����ʽ�ȴ浽һ��������
//	Cell cell[] = {{DATA,12},{DATA,3},{DATA,4},{ADD,0},{MUL,0},
//	                 {DATA,6},{SUB,0},{DATA,8},{DATA,2},{DIV,0},{ADD,0}};
//
//	int num = CalcRpn(cell,sizeof(cell)/sizeof(cell[0]));
//	if(-1 == num)
//	{
//		cout<<"���ʽ���Ϸ������������еĳ���Ϊ0"<<endl;
//	}
//	else
//	{
//		cout<<num<<endl;
//	}
//
//
//	return 0;
//
//}


//***********************����ƥ������********************************
//�������ŵ�ƥ�����⣬������ջ���ܺõĽ���� 
//1. ���������ţ�����ջ�� 
//2. ���������ţ��жϴ�ʱջ�Ƿ�Ϊ�ա� 
//* ջΪ�գ�˵�������Ŷࡣ 
//* ��Ϊ�գ��ж�ջ��Ԫ������������Ƿ��Ӧ������Ӧ��˵����ƥ�䡣��{(};��ƥ�����ջ�� 
//3. ��󣬱�������Str��,��ջΪ�գ�˵����ȫƥ�䣬��ջ���գ�˵�������Ŷࡣ

//#include<iostream>
//#include<stack>
//using namespace std;
//#include<assert.h>
//
//void CheckMatch(char* p)
//{
//	stack<char> s;//����һ��ջ
//
//	while(*p)
//	{
//		if(*p =='('|| *p =='['|| *p == '{')//���������ţ�����ջ��
//		{
//			s.push(*p);
//			p++;
//		}
//		else if(*p ==')'|| *p ==']'|| *p == '}')//���������ţ��жϴ�ʱջ�Ƿ�Ϊ��
//		{
//			if(s.empty())//ջΪ�գ�˵�������Ŷ�
//			{
//				cout<<"�����ű������Ŷ�"<<endl;
//				exit(1);
//			}
//			else//��Ϊ�գ��ж�ջ��Ԫ������������Ƿ��Ӧ
//			{
//				if(((s.top()=='(')&&(*p==')')) || ((s.top()=='[')&&(*p==']')) || ((s.top()=='{')&&(*p=='}')))
//				{
//					s.pop();//ƥ�����ջ
//					p++;
//				}
//				else//����Ӧ��˵����ƥ��
//				{
//					cout<<"���Ų�ƥ��"<<endl;
//					exit(1);
//				}
//
//			}
//		}
//		else//���������ַ�
//		{
//			p++;
//		}
//	}
//
//	//�ܳ�ѭ��֤���ַ���������ϡ���ʱջ��ֻ�������������1>��Ϊ�գ���ֻʣ���������ˣ��������ƥ��ʧ��;2>Ϊ�գ�ƥ��ɹ�
//	if(s.empty())
//	{
//		cout<<"ƥ��ɹ�"<<endl;
//	}
//	else
//	{
//		cout<<"�����ű������Ŷ�"<<endl;
//	}
//
//}
//int main()
//{
//	//char str[] = "(())abc{[(])}";//���Ų�ƥ��
//	//char str[] = "(()))abc{[]}";//�����Ŷ���������
//	//char str[] = "(()()abc{[]}";//�����Ŷ���������
//	char str[] = "(())abc{[]()}";//ƥ��ɹ�
//	CheckMatch(str);
//	return 0;
//}



