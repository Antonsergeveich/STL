#include<iostream>
#include<map>
#include<time.h>
#include <list>
using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#define TIME int min, int hour,int day, string month, int year

std::map<int, std::string> violation =
{
	{1, "Выпивший"},
	{2, "Пересечение двойной сплошной"},
	{3, "Остановка запрещена"},
	{4, "Стоянка запрещена"},
	{5, "Превышение скорости"},
	{6, "Не пристёгнут ремень безопасности"},
	{7, "Проезд на красный сигнал светофора"},
	{8, "Не подчинение сотруднику полиции"},
};



class Violation
{
	int number; // номер правонарушения
	std::string address; // адрес правонарушения
	int min, hour, day, year;
	string month;
public:
	int get_number()const
	{
		return number;
	}
	const std::string& get_address()const
	{
		return address;
	}
	int get_min()const
	{
		return min;
	}
	int get_hour()const
	{
		return hour;
	}
	int get_day()const
	{
		return day;
	}
	const std::string& get_month()const
	{
		return month;
	}
	int get_year()const
	{
		return year;
	}
	void set_number(int number)
	{
		this->number = number;
	}
	void set_address(const std::string& address)
	{
		this->address = address;
	}
	void set_min(int min)
	{
		if (min == 0 || min < 60)this->min = min;
		else cerr << "Error min! ";
	}
	void set_hour(int hour)
	{
		if (hour == 0 || hour < 24)this->hour = hour;
		else cerr << "Error hour! ";
	}
	void set_day(int day)
	{
		if (day == 0 || day < 32)this->day = day;
		else cerr << "Error day! ";
	}
	void set_month(const std::string& month)
	{
		this->month = month;
	}
	void set_year(int year)
	{
		this->year = year;
	}
	Violation(int number, const std::string& address, TIME)
	{
		set_number(number);
		set_address(address);
		set_min(min);
		set_hour(hour);
		set_day(day);
		set_month(month);
		set_year(year);
	}
	~Violation() {}
};

std::ostream& operator<<(std::ostream& os, const Violation& obj)
{
	//https://legacy.cplusplus.com/reference/map/map/operator[]/
	return os << violation[obj.get_number()] << "\tthe offense\t" << obj.get_address()<< "\t" << obj.get_min() << " минут, " << obj.get_hour() << " часов, " << obj.get_day() << " " << obj.get_month() << ", " << obj.get_year() << "г.";
}

std::map<std::string, std::list<Violation>> base =
{
	{"a333aa", {Violation(8, " st.Kozlova ", 12, 8, 7, "september", 2000)}},
	{"b111bb", {Violation(7, " st.Medvedeva ", 1,2,3," july ", 1998)}},
	{"c222cc", {Violation(6, " st.Kurochkina ", 4, 5, 6, " august ", 2001)}},
};

void main()
{
	setlocale(LC_ALL, "");
	Violation V(1, " st.Pushkina", 44, 16, 5, "september", 2021);
	Violation A(2, " st.Lermontova", 03, 16, 5, "september", 2021);
	Violation B(3, " st.Ivanova", 12, 16, 5, "september", 2021);
	Violation C(4, " st.Petrova", 3, 16, 5, "september", 2021);
	Violation D(5, " st.Sidorova", 56, 16, 5, "september", 2021);
	cout << V << endl;
	cout << A << endl;
	cout << B << endl;
	cout << C << endl;
	cout << D << endl;
	cout << endl;
	for (std::map<std::string, std::list<Violation>>::iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << "\t";
		for (std::list<Violation>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit)
		{
			cout << * vit << endl;
		}
	}
}