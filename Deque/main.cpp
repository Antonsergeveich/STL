#include<iostream>
#include <new.h>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
class Queue;

class List
{
	class Element
	{
		int Data;      
		Element* pNext;
		Element* pPrev;

	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class List;
		friend class Queue;
	}*Head, * Tail;  
	size_t size; 
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		//             Comparison operators:
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		//              Dereference operators (операторы разыименования):
		const int& operator*()const
		{
			return Temp->Data;
		}
		friend class Queue;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		friend class Queue;
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//                 Incremento/Decremento:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		friend class Queue;
	};
	
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
		friend class Queue;
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
		friend class Queue;
	};

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator rend()const
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	List(const List& other) : List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//                 Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//                 Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		else
		{
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return; 
		if (Head == Tail) 
		{
			delete Head;           
			Head = Tail = nullptr; 
			size--;
			return;
		}
		Head = Head->pNext;     
		delete Head->pPrev;     
		Head->pPrev = nullptr;  
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front(); 
		Tail = Tail->pPrev;     
		delete Tail->pNext;     
		Tail->pNext = nullptr;  
		size--;
	}
	void insert(int Data, int index)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	void erase(int index)
	{
		if (index >= size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Temp->pPrev->pNext = Temp->pNext; 
		Temp->pNext->pPrev = Temp->pPrev; 
		delete Temp;                      
		size--;
	}

	//                      Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
	friend class Queue;
};

List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
	}
	return buffer;
}
//https://legacy.cplusplus.com/reference/queue/queue/
class Queue :public List {};

void main()
{
	setlocale(LC_ALL, "");
	Queue Q;
	Q.push_back(256);
	Q.push_back(128);
	Q.push_back(64);
	Q.push_back(32);
	Q.push_back(16);
	Q.push_back(8);
	Q.print();
	Q.pop_front();
	Q.print();
	Q.erase(3);
	Q.print();
	Q.reverse_print();
}