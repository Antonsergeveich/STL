//Standard Template Library - стандартная шаблонная библиотека.
//Представляет собой набор контейнеров и инструментов для работы с ними.
//Контейнер - это объект который организует хранение других объектов в памяти.
//Каждый контейнер для хранения данных использует определённую структуру данных.
//Это может быть массив(статический или динамический), список(односвязный или двусвязный),
//дерево - это структура данных каждый элемент которой имеет два потомка: левый и правый.
//Левый потомок хранит значение меньше текущего элемента, правый больше.
//Поэтому дерево всегда отсортировано.
#include<iostream>
#include<array>
#include<vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------\n"
//#define STL_ARRAY
#define STL_VECTOR

template<typename T>void vector_properties(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	const int SIZE = 5;
	std::array<int, SIZE> arr = { 3, 5, 8 };
	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//arr.
#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные ввиде динамического массива.
	//это единственный контейнер у которого есть вместительность,
	//и который резервирует память для последующего использования.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_properties(vec);
	vec.push_back(144);
	vector_properties(vec);
#endif // STL_VECTOR
	
}
template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl; //вместительность
	cout << "Max_size:" << vec.max_size() << endl;
	cout << delimiter << endl;
}