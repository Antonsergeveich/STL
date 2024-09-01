#include<iostream>
#include<map>
#include<vector>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------\n"

//#define STL_MAP
//#define MULTIMAP
// ��� ������������� ���������� ������ ������ ����� ��������� ������.
// ������: map, set, multimap, multiset.
void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_MAP
	// map - ��� ���������, ������ ������� �������� ������ ���� <����, ��������>
	// pair <key, value>
	// ���� � �������� ����� ���� ������ ������������� ����, ��� ������ ��� � ������
	// ���������� � �������� ������ �������������� �� �����. ����� �������� �����������
	// ������� map - ����� ���������, multimap - ��������� ������� ��������� ���������� ������

	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Sunday"), // ����� �������� ����
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		{4, "Thursday"},  //  �� ����� �������� ����
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{7, "Sunday"},
	};

	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
#endif // STL_MAP

#ifdef MULTIMAP
	std::multimap<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Sunday"), // ����� �������� ����
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		std::pair<int, std::string>(3, "Wednesdayday"),
		{4, "Thursday"},  //  �� ����� �������� ����
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{7, "Sunday"},
	};

	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
#endif // MULTIMAP

	std::map<std::string, std::vector<std::string>> dictionary =
	{
		std::pair<std::string, std::vector<std::string>>("map", {"�����, ����, �������"}),
		std::pair<std::string, std::vector<std::string>>("window", {"����", "�������"}),
		{"statement", {"�����������", "���������", "������������"}},
		{"journey", {"�����������", "�������", "����"}},
	};
	/*for (std::map<std::string, std::vector<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout.width(16);
		cout << std::left;
		cout << (*it).first + ":";
		for (std::vector<std::string>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt;
			cout << (*jt != it->second.back()?", ":";");
		}
		cout << endl;
	}*/

	cout.width(16);
	cout << std::left;
	for (auto& map : dictionary)
	{
		cout.width(16);
		cout << std::left;
		cout << map.first << tab;
		for (auto& c : map.second)cout << c << tab;
		cout << endl;
	}

};