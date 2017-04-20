#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
public:

	Date()	//���캯��
	{
		_year = 0;
		_month = 0;
		_day = 0;
	}

	Date(int year, int month, int day)	//���캯��
	{
		if((year > 0)&&(month >0 && month <13)&&(day >0 && day<=GetDays(year,month)))	// ���ںϷ��Լ��
		{
			_year = year;
			_month = month;
			_day = day;

		}
		else
		{
			cout<<"��������ڲ��Ϸ������������룡"<<endl;
		}
	}

	Date(const Date& d1)	//�������캯��
	{
		_year = d1._year;
		_month = d1._month;
		_day = d1._day;
	}

	~Date()	//��������
	{}
	friend ostream& operator<<(ostream& _cout, const Date& d);//��Ԫ<<��������غ���������
	Date& operator=(const Date& d);
	Date operator+(int days);
	Date operator-(int days);
	int operator-(const Date& d);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	bool  Date::operator>(const Date& d);
	bool Date::operator<(const Date& d);
	bool Date::operator==(const Date& d);
	bool Date::operator!=(const Date& d);
	bool IsLeapyear(int year);	//�ж��Ƿ�������
	int Date::GetDays(int year,int month);	//���ĳ��ĳ�µ�����


private:
	int _year;
	int _month;
	int _day;
};



#endif