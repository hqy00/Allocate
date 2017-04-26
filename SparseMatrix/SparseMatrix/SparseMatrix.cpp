//��ҵ���ƣ�ϡ������ѹ���洢
#include<iostream>
#include<vector>
using namespace std;
#include<assert.h>

template<class T>
class SparseMatrix
{
	//��Ԫ�飨�У��У����ݣ�
	template<class T>
	struct Trituple
	{
		Trituple(size_t row, size_t col, const T& data)//���ι���
			: _row(row)
			, _col(col)
			, _data(data)
		{}

		Trituple()//�޲ι���
		{}

		size_t _row;
		size_t _col;
		T _data;
	};

public:
	
	// ϡ������ѹ���洢

	SparseMatrix()//�޲ι���
	{}
     
	SparseMatrix(T* array, size_t r, size_t c, const T& invalid)//���ι���
		: _r(r)
		, _c(c)
		, _invalid(invalid)
	{
		for(size_t i = 0;i < _r; ++i)
		{
			for(size_t j = 0;j < _c; ++j)
			{
				if(invalid != array[i * _c + j])
				{
					Trituple<T> tmp(i,j,array[i*_c + j]);
					_sm.push_back(tmp);
				}
			}
		}
	}

    //����ϡ�������r��c���е�Ԫ��
	/**�ڱ�����ЧԪ�ص�_sm�������Ҷ�Ӧ��r��c���е�Ԫ�أ��ҵ��˷���Ԫ�ص�ֵ���Ҳ���������Чֵ**/
	T& Access(int r, int c)
	{
		//��һ��forѭ����ʽ���б���
		//for(size_t i =0;i < _sm.size();++i)
		//{
		//	if(r == _sm[i]._row && c == _sm[i]._col)
		//	{
		//		return _sm[i]._data;
		//	}
		//}
		//return _invalid;


		//�ڶ����õ��������б���
		vector<Trituple<T>>::iterator it = _sm.begin();
		while(it != _sm.end())
		{
			if(r == it->_row && c == it->_col)
			{
				return it->_data;
			}
			++it;
		}
		return _invalid;

	}

    
	// ��ԭϡ�����
	/**ע�⣺��Ԫ�����������Ա������Ҫʹ����ģ�����Ҫ�Լ����¶���**/
	template<class T>	
	friend ostream& operator<<(ostream& _cout, SparseMatrix<T>& s)
	{
		//��һ����Access��ʽ,ȱ��ÿ�η���һ��Ԫ�ض�Ҫ����Accessһ��
		//for(size_t i = 0;i < s._r ; ++i)
		//{
		//	for(size_t j = 0;j < s._c; ++j)
		//	{
		//		_cout<<s.Access(i,j)<<" ";
		//	}
		//	
		//	_cout<<endl;
		//}
		//return _cout;
		
		//�ڶ�����if����ж�
		size_t index = 0;
		for(size_t i =0; i < s._r; ++i)
		{
			for(size_t j =0; j < s._c; ++j)
			{
				//һ��Ҫ��index < s._sm.size()����Լ������Ȼ��_sm������ȫ�������꣬������δ�������ʱ��
				//����forѭ����Ȼ�ܽ��룬��ʱ��if��䴦�ͻᷢ����_sm�����±�ķ��ʲ��Ϸ�
				if(index < s._sm.size() && i == s._sm[index]._row && j == s._sm[index]._col)
				{
					_cout<<s._sm[index]._data<<" ";
					++index;
				}
				else
				{
					_cout<<s._invalid<<" ";
				}
			}
			_cout<<endl;
		}
		_cout<<endl;
		return _cout;

	}

	// ϡ��������ͨ���ã�Ҫ�������ȴ洢������ʱ�临�Ӷ�
	/**���ֻ�ǽ�i,j�򵥽�������ôת�ƺ���¾����ǰ��������ȴ洢�ģ�������Ҫ�����������뵽��
	��Ϊԭ����������¾�����У������������Ƚ�ԭ�������ЧԪ�ش�����������һ�������¾�����ǰ��д洢�ġ�**/
	SparseMatrix<T> Transprot()
	{
		SparseMatrix<T> ts;
		ts._r = _c;	//ts������Ϊԭ���������
		ts._c = _r;	//ts������Ϊԭ���������
		ts._invalid = _invalid;

		//�õ�i����ԭ����_sm�����е�������Чֵ���������бȽϣ�������һ���ͽ�����Чֵ���浽�¾����_sm������
		//����ʱҪ�ǵý����к��У���Ϊԭ������������¾����������ԭ����������¾��������
		for(size_t i = 0;i < _c; ++i)
		{
			size_t index  = 0;
			while(index < _sm.size())
			{
				if(i == _sm[index]._col)
				{
					Trituple<T> tmp(i,_sm[index]._row,_sm[index]._data);
					ts._sm.push_back(tmp);
				}
				index++;
			}
		}

		return ts;
	}
	//����ЧԪ�ظ���Ϊ M ������ N �У�����ת�õ�ʱ�临�Ӷ�ΪO(N * M)

	// ϡ�����Ŀ������ã�����ʱ�临�Ӷ�
	SparseMatrix<T> FastTransprot()
	{
		// 1>ԭ������ЧԪ�ظ�����ת�ƺ���¾�����ЧԪ�صĸ�����ͬ���ȸ��¾��󿪱ٱ�����ЧԪ�ص�_sm����ռ�
		
		/**֮ǰû�и�ԭ���󿪱٣���Ϊ_sm����ʱΪ�գ�������ЧԪ���õ���push_back()���ȹ�������β�壩��
		���β�����䶯̬����_sm��,_sm�Զ����ݡ������ڲ�ȡ�ķ���������ЧԪ�ط����¾���_sm��ʱ����push_back()��
		�Ǹ����±��λ��ѡ�����ģ�������ѡ��_sm�����е�λ���ٲ���ķ�ʽ�����ڸչ���õĿյ�_sm,
		�±�����ǲ��Ϸ������Ա����ȿ��ٺ�_sm�Ŀռ�**/

		SparseMatrix<T> fts;
		fts._r = _c;	//fts������Ϊԭ���������
		fts._c = _r;	//fts������Ϊԭ���������
		fts._invalid = _invalid;
		size_t _size = _sm.size();	//��ȡԭ����_sm�Ŀռ��С
		fts._sm.resize(_size);	//���¾����_sm������һ����СΪ_size�Ŀռ䣬�ռ����ֵ0

		// 2>ͳ��ԭ������ÿһ���ж��ٸ���ЧԪ��
		int* Pcount = new int[_c];	//������СΪ����_c�Ķ�̬����Pcount,�����ʼֵΪ0
		memset(Pcount,0,_c*sizeof(Pcount[0]));
		for(size_t i = 0; i < _sm.size(); ++i)
		{
			Pcount[_sm[i]._col]++; 

		}

		// 3>ͳ��ԭ����ÿһ�еĵ�һ����Ч���ݣ���ת�ƺ��¾������Ч����_sm�е���ʼλ�ã��±꣩
		
		int* Paddr = new int[_c];//������СΪ����_c�Ķ�̬����Paddr�������ʼֵΪ0
		memset(Paddr,0,_c*sizeof(Paddr[0]))
		//��Ϊ�����ʼֵΪ0������һ�е���ʼ��ַ����Ϊ0�����ԾͲ��ùܵ�һ�е���ʼ��ַ��
		for(size_t i = 1; i <_c; ++i)
		{
			Paddr[i] = Paddr[i-1] + Pcount[i-1];
		}

		// 4>����Ԫ�ص��¾������Ч����_sm��
		for(size_t i =0; i < _sm.size(); ++i)
		{
			int& addr = Paddr[_sm[i]._col];
			fts._sm[addr] = Trituple<T> (_sm[i]._col,_sm[i]._row,_sm[i]._data);
			++addr;
		}

		delete[] Pcount;
		delete[] Paddr;

		return fts;

	}

	//����ЧԪ�ظ���Ϊ M ������ N �У�����ת�õ�ʱ�临�Ӷ�ΪO(M)+O(N)
	
	
	// ʵ��ϡ�����ļӷ�����(����һ)
	/*˼�룺���������󶼵�һά���鴦���Ƚϸ�����ЧԪ����һά�����е��±꣬ȷ��˭�ȴ���ret��_sm�С�
	���±���ͬʱ���ڸ�λ����ͣ����жϺ��Ƿ�Ϊ��Чֵ��������Чֵ������ret��_sm�У������򲻷š�*/
	SparseMatrix<T> operator+(const SparseMatrix<T>& sp)
	{
		// 1>�ж����������Ƿ�ͬ��ͬ��
		assert(_r == sp._r && _c == sp._c);
		
		// 2>������ֵret����ֵ
		SparseMatrix<T> ret;
		ret._r = _r;
		ret._c = _c;
		ret._invalid  = _invalid;
		size_t iLdex = 0, iRdex = 0;	//������������

		// 3>left �� right �ıȽ�
		while(iLdex < _sm.size() && iRdex < sp._sm.size())
		{
			//��һά���鴦���ҵ���ЧԪ���ڸ���һά�����е��±꣬�Ƚ��±��С���в���
			size_t left = _sm[iLdex]._row * _c + _sm[iLdex]._col;
			size_t right = sp._sm[iRdex]._row * _c + sp._sm[iRdex]._col;
			if(left < right)
			{
				ret._sm.push_back(Trituple<T>(_sm[iLdex]._row,_sm[iLdex]._col,_sm[iLdex]._data));
				++iLdex;
			}
			else if(left > right)
			{
				ret._sm.push_back(Trituple<T>(sp._sm[iRdex]._row,sp._sm[iRdex]._col,sp._sm[iRdex]._data));
				++iRdex;
			}
			else//�±���ͬ�����
			{
				Trituple<T> temp(_sm[iLdex]);
				temp._data += sp._sm[iRdex]._data;

				if(temp._data)//�жϺ��Ƿ�Ϊ��Чֵ
				{
					ret._sm.push_back(temp);//������Чֵ������ret��_sm��
				}
				++iLdex;
				++iRdex;
			}
		}

		//�ұ߾����_sm�����ȱ�����������߾����_sm�����л���ʣ�࣬����ߵ�ʣ�����ret��_sm��
		while(iLdex < _sm.size())
		{
			ret._sm.push_back(Trituple<T> (_sm[iLdex]._row,_sm[iLdex]._col,_sm[iLdex]._data));
			++iLdex;
		}


		//��߾����_sm�����ȱ����������ұ߾����_sm�����л���ʣ�࣬���ұߵ�ʣ�����ret��_sm��
		while(iRdex < sp._sm.size())
		{
			ret._sm.push_back(Trituple<T> (sp._sm[iRdex]._row,sp._sm[iRdex]._col,sp._sm[iRdex]._data));
			++iRdex;
		}

		return ret;
	}

	// ʵ��ϡ�����ļӷ�����(������)
	/*˼�룺�ȱȽ���ЧԪ���ڸ��Ծ����е���λ�ã�ȷ��˭�ȴ���ret��_sm�С�����λ����ͬʱ��
	�ٱȽ���λ�ã�ȷ��˭�ȴ���ret��_sm�������ж���ͬ���ڸ�λ����ͣ����жϺ��Ƿ�Ϊ��Чֵ��
	����Чֵ���ͽ���ͺ�Ĳ��룬���򲻲��롣*/
	SparseMatrix<T> operator+(const SparseMatrix<T>& sp)
	{
		// 1>�ж����������Ƿ�ͬ��ͬ��
		assert(_r == sp._r && _c == sp._c);

		// 2>������ֵret����ֵ
		SparseMatrix<T> ret;
		ret._r = _r;
		ret._c = _c;
		ret._invalid  = _invalid;
		size_t i = 0, j = 0; //������������

		// 3> �С���λ�õıȽ�
		while(i < _sm.size() && j < sp._sm.size())
		{
			//�������ЧԪ�ص���λ�� С�� �Ҿ�����ЧԪ�ص���λ��
			if(_sm[i]._row < sp._sm[j]._row)
			{
				ret._sm.push_back(Trituple<T> (_sm[i]._row,_sm[i]._col,_sm[i]._data));//�����������ЧԪ��
				++i;
			}
			//�Ҿ�����ЧԪ�ص���λ�� С�� �������ЧԪ�ص���λ��
			else if(_sm[i]._row > sp._sm[j]._row)
			{
				ret._sm.push_back(Trituple<T> (sp._sm[j]._row,sp._sm[j]._col,sp._sm[j]._data));//�����Ҿ�����ЧԪ��
				++j;
			}
			//���Ҿ�����ЧԪ�ص���λ����ͬ���Ƚ���λ��
			else
			{
				//�������ЧԪ�ص���λ�� С�� �Ҿ�����ЧԪ�ص���λ��
				if(_sm[i]._col < sp._sm[j]._col)
				{
					ret._sm.push_back(Trituple<T> (_sm[i]._row,_sm[i]._col,_sm[i]._data));//�����������ЧԪ��
					++i;
				}
				//�Ҿ�����ЧԪ�ص���λ�� С�� �������ЧԪ�ص���λ��
				else if(_sm[i]._col > sp._sm[j]._col)
				{
					ret._sm.push_back(Trituple<T> (sp._sm[j]._row,sp._sm[j]._col,sp._sm[j]._data));//�����Ҿ�����ЧԪ��
					++j;
				}
				//���Ҿ�����ЧԪ�ص���λ����ͬ����λ��Ҳ��ͬ�����
				else
				{
					Trituple<T> temp(_sm[i]);
					temp._data += sp._sm[j]._data;

					if(temp._data)//�жϺ��Ƿ�Ϊ��Чֵ
					{
						ret._sm.push_back(temp);//������Чֵ������ret��_sm��
					}
					++i;
					++j;
				}
			}
		}

		
		//�ұ߾����_sm�����ȱ�����������߾����_sm�����л���ʣ�࣬����ߵ�ʣ�����ret��_sm��
		while(i < _sm.size())
		{
			ret._sm.push_back(Trituple<T> (_sm[i]._row,_sm[i]._col,_sm[i]._data));
			++i;
		}


		//��߾����_sm�����ȱ����������ұ߾����_sm�����л���ʣ�࣬���ұߵ�ʣ�����ret��_sm��
		while(j < sp._sm.size())
		{
			ret._sm.push_back(Trituple<T> (sp._sm[j]._row,sp._sm[j]._col,sp._sm[j]._data));
			++j;
		}
		
		return ret;
	}

private:
	vector<Trituple<T>> _sm;//��̬һά�����ž�������ЧԪ�ص���Ԫ��
	size_t _r;
	size_t _c;
	T _invalid;
};


int main()
{
	int array1[6][5] = {
		{1, 0, 3, 0, 5},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 0, 3, 0, 5},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	int array2[6][5] = {
		{1, 0, -3, 0, 5},
		{0, 9, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 0, 3, 0, 5},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 7, 0}
	};

	SparseMatrix<int> SM((int *)array1,sizeof(array1)/sizeof(array1[0]),sizeof(array1[0])/sizeof(array1[0][0]),0);
	SparseMatrix<int> SP((int *)array2,sizeof(array2)/sizeof(array2[0]),sizeof(array2[0])/sizeof(array2[0][0]),0);
	//cout<<SM<<endl;
	//cout<<SM.Transprot()<<endl;
	//cout<<SM.FastTransprot()<<endl;
	cout<<SM+SP<<endl;

	return 0;
}