#pragma once
#include <iostream>

template<class T>
class List
{
	class Node
	{
	public:
		T data;
		Node* next;
		Node* prev;

		Node(const T& t, Node* n = nullptr, Node* p = nullptr);
		Node(T&& t, Node* n = nullptr, Node* p = nullptr);
	};

	Node* head;
	Node* tail;
	size_t size;

public:

	List();
	List(const List& other);
	~List();
	
	void PushBack(const T& value);
	void PushFront(const T& value);
	void Insert(T value, size_t index);

	void PopFront();
	void PopBack();
	void Remove(size_t index);
	void clear();

	unsigned int GetSize() const;
	bool IsEmpty() const;
	void Print();

	T& operator [] (size_t index) const;
	List<T>& operator = (const List<T>& other);
	List<T>& operator = (List<T>&& other);
	T& Front();
	T& Back();
	
	class Iterator;
	typename Iterator begin() const;
	typename Iterator end() const;
};

