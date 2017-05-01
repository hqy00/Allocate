#include<iostream>
#include<queue>
using namespace std;
#include<assert.h>

/**************************�ݹ�ʵ�ֶ�����**************************/

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
	void Pre()
	{
		PreOrder(_proot);
	}

	//�������������ң�
	void In()
	{
		InOrder(_proot);
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
		Node<T>* tmp;
		tmp = FindDateNode(_proot,data);
		if(NULL == tmp)
		{
			cout<<"��������û��ֵΪ�˵Ľ��"<<endl;
			exit(1);
		}
		return tmp;
	}

	//����ĳһ����˫�׽��
	Node<T>* FindParent(Node<T>* Pcur)
	{
		Node<T>* tt;
		tt = FindParentNode(_proot,Pcur);	
		if(NULL == tt)
		{
			cout<<"�������Ϊ�����,�����û��˫��"<<endl;
			exit(1);
		}
		return tt;
	}

	//��ȡĳһ��������
	Node<T>* FindLeftChild(Node<T>* Pcur)
	{
		Node<T>* tt;
		tt = FindLeftNode(_proot,Pcur);	
		if(NULL == tt)
		{
			cout<<"�����������Ӳ�����"<<endl;
			exit(1);
		}
		return tt;
	}
	
	//��ȡĳһ�����Һ���
	Node<T>* FindRightChild(Node<T>* Pcur)
	{
		Node<T>* tt;
		tt = FindRightNode(_proot,Pcur);	
		if(NULL == tt)
		{
			cout<<"���������Һ��Ӳ�����"<<endl;
			exit(1);
		}
		return tt;

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

			Node<T>* pp = NULL;
			if(pp = FindDateNode(root->_right,data))
			{
				return pp;
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

			Node<T>* pp = NULL;
			if(pp = FindParentNode(root->_right,pcur))
			{
				return pp;
			}
		}
		return NULL;
	}

	
	//��ȡĳһ��������
	Node<T>* FindLeftNode(Node<T>* root,Node<T>* pcur)
	{
		assert(pcur);//pcur�ĺϷ��Լ��
		if(root)
		{
			if(pcur == root && NULL != root->_left)
			{	
				return root->_left;
			}
				
			Node<T>* qq = NULL;
			if(qq = FindLeftNode(root->_left,pcur))
			{
				return qq;
			}

			Node<T>* pp = NULL;
			if(pp = FindLeftNode(root->_right,pcur))
			{
				return pp;
			}
		}
		return NULL;

	}


	//��ȡĳһ�����Һ���
	Node<T>* FindRightNode(Node<T>* root,Node<T>* pcur)
	{
		assert(pcur);//pcur�ĺϷ��Լ��
		if(root)
		{
			if(pcur == root && NULL != root->_right)
			{
				return root->_right;
			}
				
			Node<T>* qq = NULL;
			if(qq = FindRightNode(root->_left,pcur))
			{
				return qq;
			}

			Node<T>* pp = NULL;
			if(pp = FindRightNode(root->_right,pcur))
			{
				return pp;
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

private:
	Node<T>* _proot;//�����

};




int main()
{
	int array1[] = {1,2,4,'#','#','#',3,5,'#','#',6};
	int array2[] = {1,2,4,'#',5,'#','#',6};
	BinaryTree<int> t1(array1,sizeof(array1)/sizeof(array1[0]),'#');
	BinaryTree<int> t2(t1);
	BinaryTree<int> t3(array2,sizeof(array2)/sizeof(array2[0]),'#');
	t3 = t1;

	Node<int>* tmp1;
	tmp1 = t1.FindBinaryTree(2);
	cout<<tmp1->_value<<endl;
	t1.Pre();
	cout<<endl;
	t1.In();
	cout<<endl;
	t1.Post();
	cout<<endl;
	t1.Level();
	cout<<endl;

	Node<int>* tmp2;
	tmp2 = t1.FindParent(tmp1);
	cout<<tmp2->_value<<endl;

	Node<int>* tmp3;
	tmp3 = t1.FindLeftChild(tmp1);
	cout<<tmp3->_value<<endl;

	Node<int>* tmp4;
	tmp4 = t1.FindRightChild(tmp1);
	cout<<tmp4->_value<<endl;

	return 0;
}