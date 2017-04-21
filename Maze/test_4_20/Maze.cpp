//���ݷ�˼��ʵ���Թ����ݹ�ʵ�֣�,Ҫ�����£�
//�����Թ��ĵ�ͼ���ɶ�̬��
//�Թ������ݱ������ļ���
//��������Ӹ�������

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

#define MAX_ROW  10
#define MAX_COL  10

struct Seat//�����
{
	Seat(int x, int y)
		: _x(x)
		, _y(y)
	{}
	int _x;
	int _y;
};

// ���ݱ��浽�ļ�
class Maze
{
public:
	Maze(int Row, int Col)//���Թ���ͼ�������
	{
		FILE* mz = fopen("Map.txt","r");//��.txt�ļ��ж�ȡ��ͼ
		assert(mz != NULL);

		/***************��̬��������***********************/

		//����������ÿһ�е�ַ�Ŀռ�
		_map = new int*[Row];		

		//����������ÿһ�����ݵĿռ�
		for(int idx= 0; idx < Row; idx++)
		{
			_map[idx] = new int[Col];
		}
		/**************************************************/

		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col;)
			{
				//���ļ��е�ÿ���ַ����л�ȡ�������ȡ�����ַ�������Ҫ�ģ����д����浽�����У�������ǣ���ô�������ѭ������ȡ��һ���ַ���
				char ch = fgetc(mz);
				if (ch == '0' || ch == '1')//ע���������ַ�����������
				{
					_map[i][j] = ch-'0';
					j++;//һ��Ҫע�⣬��Ϊ���ǰ��վ�����д�ģ�������֮���пո�������֮���лس������Ե�ȡ����Ϊ��0����1������ʱ��j��������
				
				}				
			}
		}

		fclose(mz);
	}

	bool IsPass(const Seat& s)//�ж��Ƿ�Ϊͨ·��1��ͨ·��0��ǽ����·��
	{
		if(s._x < 0 || s._x >= MAX_ROW || 
			s._y < 0 || s._y >= MAX_COL)//Ϊ�˲�ʹ���ʵ�����Ƿ����������⵽�ǳ���ʱ�ͷ���
			return true;


		if(1 == _map[s._x][s._y])//��1����true,��0����false
			return true;

		return false;
	}

	bool PassMaze(Seat s)//����ڵ㴫��
	{
		if(s._x < 0 || s._x >= MAX_ROW || s._y < 0 || s._y >= MAX_COL)//�ж��Ƿ�Ϊ����
			return true;

		 //�ж��Ƿ�Ϊͨ·
		if(IsPass(s))
		{
			_map[s._x][s._y] = 2;

			Seat front(s._x-1, s._y);//����
			Seat left(s._x, s._y-1); //����
			Seat right(s._x, s._y+1);//����
			Seat down(s._x+1, s._y); //����

			if(PassMaze(front))//�ݹ�
			{
				return true;
			}
			else if(PassMaze(left))//�ݹ�
			{
				return true;
			}
			else if(PassMaze(right))//�ݹ�
			{
				return true;
			}
			else if(PassMaze(down))//�ݹ�
			{
				return true;
			}
			else
			{
				_map[s._x][s._y] = 3;
			}
		}

		return false; //��ʼ����
	}

	void PrintMaze()
	{
		for (int i = 0; i < MAX_ROW; ++i)
		{
			for (int j = 0; j < MAX_COL;++j)
			{
				cout<<_map[i][j]<<" ";
				
			}
			cout<<endl;
		}
		cout<<endl;
	}


	~Maze()//����(���ٶ�̬���ٵ�����)
	{ 
		//�ͷű�����ÿһ�����ݵĿռ�
		for(int idx=0; idx< MAX_ROW; idx++)
		{
			delete[] _map[idx];
		}

		 //�ͷű�����ÿһ�е�ַ�Ŀռ�
		delete[] _map;
	}

private:
	int** _map;

};


int main()
{
		Maze maze(MAX_ROW, MAX_COL);
		maze.PrintMaze();
		maze.PassMaze(Seat(9, 6));
		maze.PrintMaze();
		return 0;
}


//���ս����
//1.�ɹ�����ڵ��߳�ȥ�ˡ���ô����ںͳ��ڼ䣬��һ����2��ɵ�·��
//2.ʧ���ˡ���ô����ںͳ��ڼ䣬�������һ����2��ɵ�·���������Թ������һ�������������ɵ�·����Щ
//�������Թ�����ʧ�ܺ���ݻ�ȥ��·�ߣ�����Щ��3��ɵ�·���ն����������ڵ��ȥ�ˡ�



//ѭ��ʵ���Թ�����ջ��ʵ�֣�

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
using namespace std;
#include<assert.h>


#define MAX_ROW  10
#define MAX_COL  10

struct Seat//�����
{
	Seat(int x = 0, int y = 0)
		: _x(x)
		, _y(y)
	{}
	int _x;
	int _y;
};

// ���ݱ��浽�ļ�
class Maze
{
public:
	Maze(int Row, int Col)//���Թ���ͼ�������
	{
		FILE* mz = fopen("Map.txt","r");//��.txt�ļ��ж�ȡ��ͼ
		assert(mz != NULL);

		/***************��̬��������***********************/

		//����������ÿһ�е�ַ�Ŀռ�
		_map = new int*[Row];		

		//����������ÿһ�����ݵĿռ�
		for(int idx= 0; idx < Row; idx++)
		{
			_map[idx] = new int[Col];
		}
		/**************************************************/

		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col;)
			{
				//���ļ��е�ÿ���ַ����л�ȡ�������ȡ�����ַ�������Ҫ�ģ����д����浽�����У�������ǣ���ô�������ѭ������ȡ��һ���ַ���
				char ch = fgetc(mz);
				if (ch == '0' || ch == '1')//ע���������ַ�����������
				{
					_map[i][j] = ch-'0';
					j++;//һ��Ҫע�⣬��Ϊ���ǰ��վ�����д�ģ�������֮���пո�������֮���лس������Ե�ȡ����Ϊ��0����1������ʱ��j��������
				
				}				
			}
		}

		fclose(mz);
	}

	bool IsPass(const Seat& pos)//�ж��Ƿ�Ϊͨ·��1��ͨ·��0��ǽ����·��
	{
		if(pos._x < 0 || pos._x >= MAX_ROW || 
			pos._y < 0 || pos._y >= MAX_COL)//Ϊ�˲�ʹ���ʵ�����Ƿ����������⵽�ǳ���ʱ�ͷ���
			return true;


		if(1 == _map[pos._x][pos._y])//��1����true,��0����false
			return true;

		return false;
	}

	bool PassMaze(Seat pos)//����ڵ㴫��
	{
		stack<Seat> s;
		s.push(pos);

		while(!s.empty())
		{
			Seat &cur = s.top();
			Seat next;
			
			if(cur._x < 0 || cur._x >= MAX_ROW || cur._y < 0 || cur._y >= MAX_COL)//�ж��Ƿ�Ϊ����
				return true;

			_map[cur._x][cur._y] = 2;//�߹��ĵ���Ϊ2

			next = cur;//����
			--next._x ;
			if(IsPass(next))
			{
				s.push(next);
				continue;
			}

			
			next = cur;//����
			--next._y ;
			if(IsPass(next))
			{
				s.push(next);
				continue;
			}

			next = cur;//����
			++next._y ;
			if(IsPass(next))
			{
				s.push(next);
				continue;
			}

			next = cur;//����
			++next._x ;
			if(IsPass(next))
			{
				s.push(next);
				continue;
			}

			//�õ㸽��û��ͨ· 
			Seat prev = s.top();  
			_map[prev._x][prev._y] = 3;//�˻صı��Ϊ3  
		    s.pop(); 

		}

		return false;//���Թ�û��ͨ·����ʱջΪ��
	}

	void PrintMaze()
	{
		for (int i = 0; i < MAX_ROW; ++i)
		{
			for (int j = 0; j < MAX_COL;++j)
			{
				cout<<_map[i][j]<<" ";
				
			}
			cout<<endl;
		}
		cout<<endl;
	}


	~Maze()//����(���ٶ�̬���ٵ�����)
	{ 
		//�ͷű�����ÿһ�����ݵĿռ�
		for(int idx=0; idx< MAX_ROW; idx++)
		{
			delete[] _map[idx];
		}

		 //�ͷű�����ÿһ�е�ַ�Ŀռ�
		delete[] _map;
	}

private:
	int** _map;

};


int main()
{
		Maze maze(MAX_ROW, MAX_COL);
		maze.PrintMaze();
		maze.PassMaze(Seat(9, 6));
		maze.PrintMaze();
		return 0;
}

