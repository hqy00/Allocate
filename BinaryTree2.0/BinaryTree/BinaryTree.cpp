#include<iostream>
#include<queue>
#include<stack>
using namespace std;
#include<assert.h>

/**************************�������Ļ���������������**************************/

//��������������Ϣ
template<typename T>
struct Node
{
	Node(const T& x = T())//����
		:_value(x)
		,_left(NULL)
		,_right(NULL)
	{}

	Node<T>* _left;		//����
	Node<T>* _right;	//�Һ���
	T _value;	//����ֵ

};

//���������
template<typename T>
class BinaryTree
{
public:

	//�޲ι���
	BinaryTree()
		:_root(NULL)
	{}

	//���ι���
	BinaryTree(const T array[],size_t size,const T& invalued)
	{
		size_t index = 0;
		CreatBinaryTree(_proot,array,size,invalued,index);//����������

	}

	//��������
	BinaryTree(const BinaryTree<T>& bt)
	{
		_proot = CopyBinaryTree(bt._proot);
	}

	//��ֵ���������
	BinaryTree<T>&  operator =(const BinaryTree<T>& bt)
	{
		if(this != &bt)
		{
			DestoryTree(_proot);//�ݻ�ԭ������
			_proot = CopyBinaryTree(bt._proot);//����һ����btһģһ���Ķ��������������㷵�ظ�_proot
		}

		return *this;
	}

	//����
	~BinaryTree()
	{
		DestoryTree(_proot);//�ݻٶ�����
	}

public:
	
	//ǰ�����(������)
	void Pre()//�ݹ��
	{
		PreOrder(_proot);
	}
	
	void Pre_Nor1()//�ǵݹ��1
	{
		//ջ����
		if(NULL == _proot)
		{
			return;
		}

		//�ø�����ջ
		stack<Node<T>*> s;
		s.push(_proot);

		while(!s.empty())
		{
			//ȡջ��Ԫ�ط���
			Node<T>* pcur = s.top();
			cout<<pcur->_value<<" ";
			s.pop();//ɾ��ջ��Ԫ��
			if(pcur->_right)//�Ƚ����Һ�����ջ
				s.push(pcur->_right);
			if(pcur->_left)//�ٽ�������ջ
				s.push(pcur->_left);
		}

	}

	void Pre_Nor2()//�ǵݹ��2
	{
		//�ø�����ջ
		stack<Node<T>*> s;
		s.push(_proot);

		while(!s.empty())
		{
			Node<T>* pcur = s.top();//ȡջ��Ԫ��
			s.pop();//ɾ��ջ��Ԫ��
			while(pcur)
			{
				//���ʸý��
				cout<<pcur->_value<<" ";	
				
				//���˽�����Һ��ӣ������Һ�����ջ
				if(pcur->_right)	
					s.push(pcur->_right);

				//������������
				pcur = pcur->_left;
			}
		}

	}


	//�������������ң�
	void In()//�ݹ��
	{
		InOrder(_proot);
	}

	void In_Nor()//�ǵݹ��
	{
		stack<Node<T>*> s;
		Node<T>* pcur = _proot;

		while(pcur || !s.empty())
		{
			while(pcur)
			{
				s.push(pcur);
				pcur = pcur->_left;
			}

			pcur = s.top();
			cout<<pcur->_value<<" ";
			s.pop();

			pcur = pcur->_right;
		}
	}

	//������������Ҹ���
	void Post()
	{
		PostOrder(_proot);
	}

	//�������
	void Level()
	{
		LevelOrder(_proot);
	}
	
	//���Ҷ�������ֵΪdata�Ľ��
	Node<T>* FindBinaryTree(T data)
	{
		Node<T>* tmp = FindDateNode(_proot,data);
		return tmp;
	}

	//����ĳһ����˫�׽��
	Node<T>* FindParent(Node<T>* Pcur)
	{
		Node<T>* tt = FindParentNode(_proot,Pcur);	
		return tt;
	}

	//��ȡĳһ��������
	Node<T>* FindLeftChild(Node<T>* pcur)
	{
		assert(_proot);
		if(pcur)//���pcur�Ƿ����
		{
			Node<T>* tmp = NULL;
			if(tmp = pcur->_left)
			{
				return tmp;
			}
		}
		return NULL;
	}
	
	//��ȡĳһ�����Һ���
	Node<T>* FindRightChild(Node<T>* pcur)
	{
		assert(_proot);
		if(pcur)//���pcur�Ƿ����
		{
			Node<T>* tmp = NULL;
			if(tmp = pcur->_right)
			{
				return tmp;
			}
		}
		return NULL;
	}

	//���һ�����ĸ߶�
	size_t Height()
	{
		size_t high = _height(_proot);
		return high;
	}

	//��ȡ����Ҷ�ӽ��ĸ���
	size_t LeeNode()
	{
		size_t count = _leenode(_proot);
		return count;
	}

	//��ȡ����ĳһ����ĸ���
	size_t KLevelNode(size_t k)
	{
		size_t count = _klevelnode(_proot,k);
		return count;
	}

	//�������ľ���(��ת��������)
	//�ݹ�汾
	void BinaryMirror()
	{
		 _BinaryMirror(_proot);
	}

	//�ǵݹ�汾
	void BinaryMirror_Nor()
	{
		 //����
		 if(NULL == _proot)
		 {
			 return;
		 }

		 queue<Node<T>*> q;
		 q.push(_proot);

		 while(!q.empty())
		 {
			 Node<T>* pcur = q.front();
			 if(pcur->_left)
				 q.push(pcur->_left);
			 if(pcur->_right)
				 q.push(pcur->_right);

			 std::swap(pcur->_left,pcur->_right);
			 q.pop();
		 }
	}

	
private:

	//������������ʣ�������
	void CreatBinaryTree(Node<T>*& root,const T arr[],size_t size,const size_t invalued,size_t& index)
	{
		if(index < size && arr[index] != invalued)//�ж�������˳���ܱ䣬���򽫵����±���ʲ��Ϸ�
		{
			root = new Node<T>(arr[index]);	//���������
			CreatBinaryTree(root->_left,arr,size,invalued,++index);  //����������
			CreatBinaryTree(root->_right,arr,size,invalued,++index); //����������

		}
	}

	//�������Ŀ���
	Node<T>* CopyBinaryTree(Node<T>* root)
	{
		Node<T>* NewNode = NULL;
		if(root)
		{
			NewNode = new Node<T>(root->_value);	//���������

			NewNode->_left = CopyBinaryTree(root->_left);	//����������
			NewNode->_right = CopyBinaryTree(root->_right);	//����������
		}	
		return NewNode;

	}

	//�ݻٶ�����
	void DestoryTree(Node<T>*& root)//��һ��ָ����������Զ��������в���
	{
		//���ú�����ʵķ�ʽ�Զ������еĽ���������
		if(root)
		{
			DestoryTree(root->_left);
			DestoryTree(root->_right);
			delete root;
			root = NULL;
			
		}
	}

	//���Ҷ�������ֵΪdata�Ľ��
	Node<T>* FindDateNode(Node<T>* root,T& data)
	{
		if(root)
		{
			if(data == root->_value)
			{
				return root;
			}

			Node<T>* qq = NULL;
			if(qq = FindDateNode(root->_left,data))
			{
				return qq;
			}

			if(qq = FindDateNode(root->_right,data))
			{
				return qq;
			}
		}
		return NULL;
	}

	
	//����ĳһ����˫�׽��
	Node<T>* FindParentNode(Node<T>* root,Node<T>* pcur)
	{
		assert(pcur);//pcur�ĺϷ��Լ��
		if(pcur == root)//����Ľ��Ϊ����� 
		{
			return NULL;
		}

		if(root)
		{
			if(pcur == root->_left || pcur == root->_right)
			{
				return root;
			}
				
			Node<T>* qq = NULL;
			if(qq = FindParentNode(root->_left,pcur))
			{
				return qq;
			}

			if(qq = FindParentNode(root->_right,pcur))
			{
				return qq;
			}
		}
		return NULL;
	}

	

	//ǰ�����(������)
	void PreOrder(Node<T>* root)
	{
		if(root)
		{
			cout<<root->_value <<" ";
			PreOrder(root->_left);
			PreOrder(root->_right);
		}
	}

	//�������������ң�
	void InOrder(Node<T>* root)
	{
		if(root)
		{
			InOrder(root->_left);
			cout<<root->_value <<" ";
			InOrder(root->_right);
		}
	}

	//������������Ҹ���
	void PostOrder(Node<T>* root)
	{
		if(root)
		{
			PostOrder(root->_left);
			PostOrder(root->_right);
			cout<<root->_value <<" ";
		}
	}

	//�������
	void LevelOrder(Node<T>* root)
	{
		if(NULL == root)//��Ϊ�շ���
		{
			return;
		}
		queue<Node<T>*>	q;
		q.push(root);

		while(!q.empty())
		{
			//ѡȡ��ͷԪ��
			Node<T>* pcur = q.front();

			//����ͷԪ�ص���������ѹ�����
			if(pcur->_left)
				q.push(pcur->_left);
			if(pcur->_right)
				q.push(pcur->_right);
			
			//���ʶ�ͷԪ��
			cout<<pcur->_value<<" ";
			
			//ɾ����ͷԪ��
			q.pop();
		}
		
	}

	//���һ�����ĸ߶�(���)
	size_t _height(Node<T>* root)
	{
		//����
		if(NULL == root)
		{
			return 0;
		}
		//ֻ��һ�����
		if(NULL == root->_left && NULL == root->_right)
		{
			return 1;
		}

		//�ж����㡣�������������ĸ߶ȣ�Ȼ�����ĸ߶� = Max(�������߶ȣ��������߶�) + 1
		size_t left = _height(root->_left);
		size_t right = _height(root->_right);

		return ((left > right)?left:right) + 1;
	}

	//��ȡ����Ҷ�ӽ��ĸ���
	size_t _leenode(Node<T>* root)
	{
		//����
		if(NULL == root)
		{
			return 0;
		}

		//ֻ��һ�����
		if(NULL == root->_left && NULL == root->_right)
		{
			return 1;
		}

		//�ж����㡣������������������Ҷ�ӽ�������ͺ󷵻�
		size_t left = _leenode(root->_left);
		size_t right = _leenode(root->_right);

		return left + right;

	}


	//��ȡ���е�k����ĸ���������ģ��С�������ĵ�k�����������������������������ĵ�k-1������֮��
	 size_t _klevelnode(Node<T>* root,size_t k)
	 {
		 //�϶��Ƿ�Ϊ�����Լ�k��ֵ�Ƿ�Ϸ�
		 //���k > _height(root)��������ȥ�������벻�ӽ����һ������ֽ�ϻ�һ�£������ϻ�����һ�Ρ��˴�������Ϊ�˿��ĸ�ֱ��
		 if(NULL == root || k < 1 ) 
		 {
			 return 0;
		 }

		 //��һ��ֻ��һ�������
		 if(1 == k)
		 {
			 return 1;
		 }

		 //������
		 size_t left = _klevelnode(root->_left,k-1);
		 size_t right = _klevelnode(root->_right,k-1);

		 return left + right;
	 }

	 //��������ľ���(�ݹ�)
	 void _BinaryMirror(Node<T>* root)
	 {
		 //����
		 if(NULL != root)
		 {
			 std::swap(root->_left,root->_right);
			 _BinaryMirror(root->_left);
			 _BinaryMirror(root->_right);
		 }

	 }



private:
	Node<T>* _proot;//�����

};




int main()
{
	//int array1[] = {1,2,4,'#','#','#',3,5,'#','#',6,'#',7};
	int array1[] = {1,2,4,'#','#','#',3,5,'#','#',6};
	int array2[] = {1,2,4,'#',5,'#','#',6};
	BinaryTree<int> t1(array1,sizeof(array1)/sizeof(array1[0]),'#');
	BinaryTree<int> t2(t1);
	BinaryTree<int> t3(array2,sizeof(array2)/sizeof(array2[0]),'#');
	t3 = t1;

	//Node<int>* tmp1 = t1.FindBinaryTree(3);
	//if(tmp1)
	//	cout<<"�ý��Ϊ"<<tmp1->_value<<endl;
	//else
	//	cout<<"��������û��ֵΪ�˵Ľ��"<<endl;

	//t1.Pre();
	//cout<<endl;
	//t1.In();
	//cout<<endl;
	//t1.Post();
	//cout<<endl;
	//t1.Level();
	//cout<<endl;


	//Node<int>* tmp2 = t1.FindParent(tmp1);
	//if(tmp2)
	//	cout<<"�ý���˫�׽��Ϊ"<<tmp2->_value<<endl;
	//else
	//	cout<<"�������Ϊ�����,�����û��˫��"<<endl;


	//Node<int>* tmp3 = t1.FindLeftChild(tmp1);
	//if(tmp3)
	//	cout<<"����Ϊ��"<<tmp3->_value<<endl;
	//else
	//	cout<<"�˽��û������"<<endl;


	//Node<int>* tmp4 = t1.FindRightChild(tmp1);
	//if(tmp4)
	//	cout<<"�Һ���Ϊ��"<<tmp4->_value<<endl;
	//else
	//	cout<<"�˽��û���Һ���"<<endl;


	//cout<<"������ĸ߶�Ϊ"<<t1.Height()<<endl;

	//cout<<"�������Ҷ�ӽ�����Ϊ"<<t1.LeeNode()<<endl;

	//cout<<"��һ�㹲��"<<t1.KLevelNode(3)<<"�����"<<endl;

	//t1.BinaryMirror();
	//t1.BinaryMirror_Nor();
	//t1.Pre_Nor1();
	//t1.Pre_Nor2();
	t1.In_Nor();
	cout<<endl;
	return 0;
}