#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------\n"

class Element //��������� ��������� ��������
{
	int Data;          //�������� ��������
	Element* pNext;    //Pointer to Next - ��������� �� ��������� �������
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0;
class Iterator
{
	Element* Temp;
public:
	//E0415	no suitable constructor exists to convert from "Element *" to "Iterator"
	//�� ���������� ����������� ������������ ��� ��������������
	//�� "Element *" � "Iterator".
	Iterator(Element* Temp) : Temp(Temp)
	{
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}
	//E0349	no operator "!=" matches these operands	
	//�������� "!=" �� ������������� ���� ���������
	//C2676	binary '!=': 'Iterator' does not define this operator
	//or a conversion to a type acceptable to the predefined operator	
	//C2676 �������� ��� '!=': 'Iterator' �� ���������� ���� ��������
	//��� �������������� � ����, ����������� ��� ����������������� ���������
	//C2675	unary '++': 'Iterator' does not define this operator
	//or a conversion to a type acceptable to the predefined operator
	//C2100	you cannot dereference an operand of type 'Iterator'
	//C2100 �� ������� ������������ ������� ���� 'Iterator' � ������
	//C2440	'initializing': cannot convert from 'Iterator' to 'int'
	//C2440 "�������������": �� ������� ������������� �� ������
	//'Iterator' � 'int' 
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator ==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
	int& operator*()const
	{
		return Temp->Data;
	}
};
class ForwardList //����������� ������
{
	Element* Head; //������ ������, ��������� �� ��������� ������� ������
	unsigned int size; //������ ������
public:
	Iterator begin()
		//E0020 identifier "Iterator" is undefined	
		//������������� "Iterator" �� ���������
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//����������� �� ��������� ������� ������ ������ ������
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(unsigned int size) : ForwardList() //explicit ��������� �� ����� �������������� �����
	{
		while (size--)push_front(0);
		/*for (int i = 0; i < size; i++)
		{
			push_front(rand() % 100);
		}*/
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //�������� ���������� ��� CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other); //������� std::move() ������������� �������� MoveAssignment ��� ������
		cout << "MoveConstructor:" << this << endl; //����������� �����������
	}
	//����� ������� ���������� �������� �� ��������
	//�� ����� ������ �������� ��������� ����������� ���������� ������ 
	//����� ������������ ��� ����������� ������
	//���������������� ������������ ��������� �����-�� �������,
	//����� ������ ���������� MoveAssignment, MoveConstructor
	ForwardList(const initializer_list<int>& il) : ForwardList() //Single-argument constructor
	{
		//initializer_list (������ �������������) - ��� ���������, ��� �� ��� � ForwardList
		//��������� - ��� ������, ������� ������������ �������� ������ ���������� �������� � ������.
		//� ������ ���������� � ������������ ������� ���� ��� ������: 
		// 1) begin() - ���������� �������� �� ������ ����������.
		// 2) end() - ���������� �������� �� ����� ����������.
		// initializer_list ������ ��� ������ �������� ��� 
		// ������������ ���������� �������� � �������� ������� ����� �������
		//il.
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front(); //���� Head ��������� �� �����-�� ������� (�� ��� �� ���� true) ���� ��������, �� ���� - false �����. 
		/*for (int i = 0; i = size; i++)
		{
			pop_front();
		}*/
		cout << "LDestructor:\t" << this << endl;
	}

	//                 Operators:
	ForwardList& operator = (const ForwardList& other)
	{
		if (this == &other)return *this;
		//while (Head)pop_front();
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator = (ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	const int& operator[](int index)const
		//����� ���������� �������� �� ��������
		//�� �� ����� ������ �������� ��������� ���������� ������, 
		//� ��������� ���������� ������ �� ��������� �����������, 
		//������� ���������� �� ������ ����� ������ ������ C2106, E0137
		//Error	E0137 expression must be a modifiable lvalue	
		//Error	C2106	'=': left operand must be l - value	
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//            Adding elements (���������� ��������): 
	void push_front(int Data)
	{
		////1) ������ ����� �������:
		//Element* New = new Element(Data); //�������� new �������� ����������� ������

		////2) �������������� ����� ������� � ������ ������:
		//New->pNext = Head;

		////3) ������ �������������� �� ����� �������:
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}

	void push_back(int Data)
	{
		//��������� push_back() �� ����� �������� � ������ �������, �� ���������,
		//���� ������ ����, �������� ����� push_front(), ������� ����� �������� � ������ �������.
		if (Head == nullptr)return push_front(Data); //���� ������ ������, ��������� ������� ������� ������
		//Element* New = new Element(Data); //������ ����� �������
		Element* Temp = Head; //������ ��������� �� ������� �������
		//while((*Temp).pNext)
		while (Temp->pNext)//���� ������� ������� �� ��������� �� ���� ��������� �� ��������� ������� ������
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);// ����� ���� ��� �� ��������� � ����� ������, ����� ��������� ����� �������
		size++;
	}

	//               Removing elements:

	void pop_front()
	{
		if (Head == nullptr)return; //���� ������������ �������� void, �� return ������ ��������� ������ ������� � ���������� ���������� �� ����� ������
		//1)���������� ����� ���������� ��������:
		Element* Erased = Head;
		//2)��������� ��������� ������� �� ������:
		Head = Erased->pNext;
		//3)������� ������� �� ������:
		delete Erased;
		size--;
		/*new - ������ ������ � ������������ ������
		new[] - ������ ������ �������� � ������������ ������

		delete - ������� ���� ������ � ������������ ������
		delete[] - ������� ������ �������� �� ������������ ������*/
	}

	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head; // � ����������� ������ ����� ����� ������ ����� ������
		while (Temp->pNext->pNext)//� ������� ���������� � ��������� pNext
			//�������� Temp, ������� ��������� �� pNext ���������� ��������.
			//���� ��������� pNext ���������� �������� ����� ����,
			//�� ������ �������� ���, ������� �� �����������.
			//pNext (���������), pNext-> (�������)
		{
			Temp = Temp->pNext; //�������� �� ��������� ������
		}
		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;
		//3) �������� ��������� �� ��������� �������:
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int index, int Data) //��������� ������� �� �������
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return push_front(Data);
		//if (index > size)return;
		//Element* New = new Element(Data); //�������� ������ ��� ����� �������
		Element* Temp = Head; //������ �������� ������� ����� ��������� �� ������� ������� � ������
		for (int i = 0; i < index - 1; i++) //��� �� ������ �� �������� ����� �����������
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		//New->pNext = Temp->pNext; //���������� � ����������� ������� ����� ���������� ��������
		Temp->pNext = new Element(Data, Temp->pNext); //� ������� ���������� �����������
		size++;
	}
	void erase(int index)
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return pop_front();
		Element* Temp = Head;//������ �������� � �������� ���� �� ��������� � ������ ������
		for (int i = 0; i < index - 1; i++)//��� �� ������� ��������
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext; // ��������� ��������� �������
		Temp->pNext = Temp->pNext->pNext; // ������� ������� �� ������
		delete Erased;// ������� ������� �� ������
		size--;
	}

	//                  Methods:
	void print()const
	{
		//Element* Temp = Head;   //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.  
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //������� �� ��������� �������.
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer = left;
	//for (int i = 0; i < left.get_size(); i++)buffer.push_back(left[i]);
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}
void Print(int arr[])
//� ������� ���������� ��������� �� ������ arr, � �� ���� ������,
//������� ����� �������� ���������� ��������� ����,
//� �� ���������� ��������� ����� �������, ��� ��� 
//sizeof(arr) / sizeof(arr[0]) = 4/4 = 1, � �� ������ ����� �������
//� ������ ������� �� ������ ������ �������� � ������;
{
	//cout << typeid(arr).name() << endl;
	//cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}

//#define BASE_CHECK 
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define OPERATOR_PLUS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGED_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ��������� ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(7);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

#ifdef OPERATOR_PLUS_CHECK
	//ForwardList list1;
//list1.push_back(3);
//list1.push_back(5);
//list1.push_back(8);
//list1.push_back(13);
//list1.push_back(21);
//list1.print();

//ForwardList list2;
//list2.push_back(34);
//list2.push_back(55);
//list2.push_back(89);
//list2.print();

//cout << delimiter << endl;
////ForwardList list3 = list1 + list2;	//CopyConstructor
//cout << delimiter << endl;
//ForwardList list3;
//cout << delimiter << endl;
//list3 = list1 + list2;	//CopyAssignment
//cout << delimiter << endl;
//list3.print();  
#endif // OPERATOR_PLUS_CHECK

#ifdef INITIALIZER_LIST_CONSTRUCTOR_CHECK
	ForwardList list1 = { 3,5,8,13,21 };
	//����� ������������� �� ������ ����� � ��� ���
	//����� ����������� � ����� ����������(Single-argument constructor)
	//� �������� ������������ (CopyAssignment) 
	//������ ������ ��� ������� �� ��������;
	list1.print();
#endif // INITIALIZER_LIST_CONSTRUCTOR_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	//int* arr = new int[5] {3, 5, 8, 13, 21};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for:
	for (int i : arr) //���� for �� ������ ���������; 
		//��� int ���������� i ����� �������������� ��� ���������� ����������
		//��������� ������� (sizeof(arr) / sizeof(int)) � ����� for;
	{
		cout << i << tab;
	}
https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	//Range - ��� ��������. ��� ������ �������� � ���� ��������� �������� ���������;
	//�.�. ����������� ������ �������� 'range';
	//�������������, Range-base for - ��� ���� for ��� �����������. 
	cout << endl;
	cout << typeid(arr).name() << endl;
	Print(arr);
	//delete[] arr;  
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGED_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		//Error E2291 this range - based 'for' statement requires a suitable
		//"begin" function and none was found;
		//��� ����� ��������� 'for', ����������� �� ���������,
		//��������� ���������� ������� "begin", �� ��� �� �������;
		//Error	C2672 'begin': no matching overloaded function found
		//�� ������� ��������������� ������������� �������
		//Error	C2672 'end': no matching overloaded function found	
		//Error	C3536 '<begin>$L0': cannot be used before it is initialized	
		//�� ����� ���� ����������� �� ��� �������������
		//Error	C3536 '<end>$L0': cannot be used before it is initialized	
		//Error	C2100 you cannot dereference an operand of type 'int'	
		//�� �� ������ ������������ ������� ���� 'int'
		cout << i << tab;
	}
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGED_BASED_FOR_LIST

}