#include<iostream>
#include<map>
#include<time.h>
using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

namespace GAI {};

class Timer;
class Violation;

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
	//Timer timer; // Время правонарушения
public:
	int get_number()const
	{
		return number;
	}
	const std::string& get_address()const
	{
		return address;
	}
	void set_number(int number)
	{
		this->number = number;
	}
	void set_address(const std::string& address)
	{
		this->address = address;
	}

	~Violation() {}
};

class Timer
{
protected:
	int min;
	int hour;
	int day;
	std::string month;
	int year;
public:
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
	Timer(const std::string& month)
	{
		set_month(month);
	}
	Timer(int min, int hour, int day, const std::string& month, int year)
	{
		set_min(min);
		set_hour(hour);
		set_day(day);
		set_month(month);
		set_year(year);
	}
	~Timer() {}

	friend class Violation;
};

std::ostream& operator<<(std::ostream& os, const Timer& obj)
{
	return os << obj.get_min() << " минут, " << obj.get_hour() << " часов, " << obj.get_day() << " " << obj.get_month() << ", " << obj.get_year();
}

void main()
{
	setlocale(LC_ALL, "");
	Timer timer(5,15,5,"декабря",2021);
	cout << timer;
};