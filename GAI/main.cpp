#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<map>
#include<time.h>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

std::map<int, std::string> violation =
{
	{1, "��������"},
	{2, "����������� ������� ��������"},
	{3, "��������� ���������"},
	{4, "������� ���������"},
	{5, "���������� ��������"},
	{6, "�� ��������� ������ ������������"},
	{7, "������ �� ������� ������ ���������"},
	{8, "�� ���������� ���������� �������"},
};

class Violation
{
	int number; 
	string address;
	//https://legacy.cplusplus.com/reference/ctime/time/?kw=time
	time_t timer;
public: 
	int get_number()const
	{
		return number;
	}
	const string& get_address()const
	{
		return address;
	}
	const time_t& get_time()const
	{
		return timer;
	}
	void set_number(int number)
	{
		this->number = number;
	}
	void set_address(const string& address)
	{
		this->address = address;
	}
	void set_time(time_t time)
	{
		;
	}
	
	Violation(int number, const string& address, time_t timer)
	{
		set_number(number);
		set_address(address);
		set_time(timer);
	}
	~Violation(){}
};

std::ostream& operator<<(std::ostream& os, const Violation& obj)
{
	return os << obj.get_number() << "\t" << obj.get_address() << "\t" << obj.get_time();
}
void main()
{
	setlocale(LC_ALL, "");
	Violation viola(1, "��.������", 2024);
	cout << viola << endl;
}