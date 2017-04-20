#include "date.h"

ostream& operator<<(ostream& _cout, const Date& d)	//��Ԫ<<��������غ����Ķ���
{
	_cout<<d._year<<"-"<<d._month<<"-"<<d._day;
	return _cout;
}



Date& Date::operator =(const Date &d)	//��ֵ���������
{
	if(this != &d)	//�ж��Ƿ��Լ����Լ�����
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	return *this;

}



bool  Date::IsLeapyear(int year)	//�ж��Ƿ�������
{
	if((year % 4 ==0)&&(year % 100 != 0)||(year % 400 ==0))
	{
		return true;
	}

	return false;
}

	
int Date::GetDays(int year,int month)	//���ĳ��ĳ�µ�����
{
	assert(month > 0 && month <13);
	int day[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if((month == 2)&&(IsLeapyear(year)==1))
	{
		day[2] += 1;
		return day[2];
	}

	return day[month];

}

Date Date::operator +(int days)  //ʵ������������
{
	Date temp = *this;	
	if(days < 0)	
	{
		return *this - (0 - days);	//���á�-�����������
	}

    temp._day = _day + days;	
    while (temp._day>GetDays(temp._year,temp._month))	//����Ƿ�Ӻ�����ڴ��ڵ��굱���������
    {
        temp._day -= GetDays(temp._year, temp._month);	//��������������ڼ�ȥ���굱���������
        if (temp._month < 12)	//�·ݼ�1
            temp._month++;
        else
        {
			temp._month = 1;
            temp._year++;
        }
    }
    return temp;
}


Date Date::operator-(int days)	//ʵ�ֵ���������
{
	Date temp = *this;	
	if(days < 0)
	{
		return *this + (0 - days);	//���á�+�����������
	}
    temp._day = _day - days;	//������ǰ����temp._day��
	while(temp._day <= 0)	
	{
		if(temp._month > 1 && temp._month <13)	//����Ǹ�������ǰ��һ����
		{
			temp._month--;
		}
		else
		{
			temp._month = 12;
			temp._year--;
		}
		
		temp._day += GetDays(temp._year,temp._month);//����˻�������������µ�������ڻ��Ǹ�����
													//�ظ���ѭ��,ֱ��Ϊ����
	}

	return temp;
}


int Date:: operator-(const Date& d)	//�����������ڶ���֮����������
{   
    Date max(*this);  
    Date min(d);
	int day = 0; 
    if (max < min)	//��<���������������������������ͣ����á�<�����������
	{  
        max = d;  
        min = *this;  
    }  
 
    while (1) 
	{  
       if ((min + day)== max)  //���á�+����������أ�Ҳ�����ˡ�==�����������
	   {
		   break; 
	   } 
        day++;  
    }

    return day;  
}  



Date& Date:: operator++()	//ǰ��++
{
	*this = *this + 1;		//��Ϊ��+����������������Ͷ���Ҫ���á�+�����������
	return *this;



	//int month_days = GetDays(_year,_month);		//ĳ��ĳ���ж�����
	//if(_day <��month_days)	//û�г��������������
	//{
	//	_day++;
	//}
	//else if(_day ==��month_days))	//���ڵ����������
	//{
	//	_day = 1;
	//	if(_month <12)
	//	{
	//		_month++;
	//	}
	//	else
	//	{
	//		_month = 1;
	//		_year++;
	//	}
	//}
	//else
	//{
	//	assert(false);
	//}

	//return *this;

}


Date Date::operator++(int)	//����++
{
	Date temp = *this;
	*this = *this + 1;
	return temp;
	//int month_days = GetDays(_year,_month);		//ĳ��ĳ���ж�����
	//int temp = *this;
	//if(_day <��month_days)	//û�г��������������
	//{
	//	_day++;
	//}
	//else if(_day ==��month_days))	//���ڵ����������
	//{
	//	_day = 1;
	//	if(_month <12)
	//	{
	//		_month++;
	//	}
	//	else
	//	{
	//		_month = 1;
	//		_year++;
	//	}
	//}
	//else
	//{
	//	assert(false);
	//}

	//return temp;

}



Date& Date::operator--()	//ǰ��--
{
	*this = *this - 1;		//��Ϊ��-����������������Ͷ���Ҫ���á�-�����������
	return *this;

}

Date Date::operator--(int)	//����--
{
	Date temp = *this;
	*this = *this - 1;
	return temp;

}



bool  Date::operator>(const Date& d)
{
    if ((_year > d._year) || ((_year == d._year) &&( _month > d._month) )
        || ((_year == d._year) && (_month == d._month) && (_day > d._day)))
        return true;
    else
        return false;
}

bool Date::operator<(const Date& d)
{
    if ((_year < d._year) || ((_year == d._year) && (_month < d._month))
        || ((_year == d._year) && (_month == d._month) && (_day < d._day)))
        return true;
    else
        return false;
}

bool Date::operator==(const Date& d)
{
    return ((_year == d._year) && (_month == d._month) && (_day == d._day));
}

bool Date::operator!=(const Date& d)
{
    return !(*this == d);	//��Ϊ��==�����ߵĲ��������������͵ģ����Ե��á�==�����������
}



//int main()
//{
//	Date d1(2017,2,16);
//	Date d2(2016,11,11);
//	//Date d3;
//	//d3 = d2;
//	//d3 = d1++;
//	cout<<d2-d1<<endl;
//	//cout<<d1-30<<endl;
//	//cout<<d1<<"fsfsgdfg"<<d2<<endl;
//	//system("pause");
//	return 0;
//}