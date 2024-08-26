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

//Sequence containers (линейные контейнеры или последовательные): array, vector, list, forward_list, deque.

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
	//Если на момент добавления в векторе отсутствуют свободные элементы,
	//то он переопределяет хранилище увеличивая его размер в полтора раза и благодаря этому последующие элементы добавляются в вектор максимально быстро.
	//таким образом самую дорогостоящую для массива операцию - переопределение памяти вектор выполняет настолько редко насколько это возможно.
	//Что добавляет производительности при работе с памятью за счёт использования дополнительной памяти.
	//У вектора есть начало и нет конца.
	// Аллокаторы - функция которая выделяет память.
	// Придикаты  - функция которая что-то проверяет.

	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_properties(vec);
	
	vec.push_back(144);
	vector_properties(vec);
	
	vec.resize(15);      // задаёт фактический размер вектора
	for (int i : vec)cout << i << tab; cout << endl;
	vector_properties(vec);
	
	vec.shrink_to_fit(); // урезает вместительность до фактического размера
	for (int i : vec)cout << i << tab; cout << endl;
	vector_properties(vec);

	vec.reserve(144);    // позволяет зарезервировать нужный объём памяти
	// Этот метод выполняется только в том случае если ему передать значение
	// больше текущего capacity();
	for (int i : vec)cout << i << tab; cout << endl;
	vector_properties(vec);

#endif // STL_VECTOR
	
}

// Для работы с Capacity вектор обеспечивае следующие функции: 
// resize(), reserve(), shrink_to_fit()

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl; //вместительность
	cout << "Max_size:" << vec.max_size() << endl;
	cout << delimiter << endl;
}