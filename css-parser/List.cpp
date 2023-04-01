#include "List.h"


template<class T>
List<T>::List::Node::Node(const T& t, Node* n, Node* p) {
	data = t;
	next = n;
	prev = p;
}


template<class T>
List<T>::List::Node::Node(T&& t, Node* n, Node* p) {
	data = std::move(t);
	next = n;
	prev = p;
}


template<class T>
List<T>::List()
{
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}


template<class T>
List<T>::List(const List<T>& other) {
	head = nullptr;
	tail = nullptr;
	size = 0;

	Node* cur = other.head;
	while (cur != nullptr) {
		PushBack(cur->data);
		cur = cur->next;
	}
}


template<class T>
List<T>::~List()
{
	clear();
}


template<class T>
void List<T>::PushBack(const T& value)
{
	Node* temp = new Node(value);
	if (tail == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	size++;
}


template<class T>
void List<T>::PushFront(const T& value)
{
	Node* temp = new Node(value);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		head->prev = temp;
		temp->next = head;
		head = temp;
	}
	size++;
}


template<class T>
void List<T>::Insert(T value, size_t index)
{
	if (index == 0) {
		PushFront(value);
	}
	else if (index == size) {
		PushBack(value);
	}
	else if (index > 0 && index < size)
	{
		Node* previous = head;
		for (size_t i = 0; i < index - 1; i++) {
			previous = previous->next;
		}
		Node* temp = new Node(value);
		temp->next = previous->next;
		temp->prev = previous;
		previous->next = temp;
		temp->next->prev = temp;
		size++;
	}
}


template<class T>
void List<T>::PopFront()
{
	if (head == nullptr) return;
	if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
	size--;

}

template<class T>
void List<T>::PopBack()
{
	if (size == 0) return;
	Node* temp = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete temp;
	size--;
}


template<class T>
void List<T>::Remove(size_t index)
{
	if (size == 0) {
		return;
	}
	if (index == 0) {
		PopFront();
	}
	else if (index == size - 1) {
		PopBack();
	}
	else if (index > 0 && index < size - 1)
	{
		Node* current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		size--;
	}
}


template<class T>
void List<T>::clear()
{
	while (size > 0) {
		PopFront();
	}
}


template<class T>
unsigned int List<T>::GetSize() const
{
	return size;
}


template<class T>
bool List<T>::IsEmpty() const
{
	return size == 0;
}


template<class T>
void List<T>::Print()
{
	for (size_t i = 0; i < this->GetSize(); i++) {
		std::cout << this->operator[](i);
	}
	std::cout << std::endl;
}


template<class T>
T& List<T>::operator [] (size_t index) const
{
	Node* current;
	if (index < size / 2) {
		current = head;
		for (size_t i = 0; i < index; i++) {
			current = current->next;
		}
	}
	else if (index < size) {
		current = tail;
		for (size_t i = size - 1; i > index; i--) {
			current = current->prev;
		}
	}
	else {
		throw std::out_of_range("Index out of range");
	}
	return current->data;
}


template<class T>
List<T>& List<T>::operator = (const List<T>& other) {
	if (this != &other) {
		clear();
		Node* currentNode = other.head;
		
		while (currentNode != nullptr) {
			PushBack(currentNode->data);
			currentNode = currentNode->next;
		}
	}
	return *this;
}

template<class T>
List<T>& List<T>::operator = (List<T>&& other)
{
	if (this == &other) {
		return *this;
	}
	clear();
	head = other.head;
	tail = other.tail;
	size = other.size;
	
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
	return *this;
}


template<class T>
T& List<T>::Front()
{
	return this->head->data;
}

template<class T>
T& List<T>::Back()
{
	return this->tail->data;
}


template <class T>
class List<T>::Iterator
{
	Node* node_;

public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = std::ptrdiff_t;

	Iterator(Node* node = nullptr) : node_(node) {}

	Iterator& operator ++ () {
		node_ = node_->next;
		return *this;
	}

	Iterator operator ++ (int) {
		Iterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator == (const Iterator& other) const {
		return node_ == other.node_;
	}

	bool operator != (const Iterator& other) const {
		return !(*this == other);
	}

	reference operator * () const {
		return node_->data;
	}

	pointer operator -> () const {
		return &node_->data;
	}
};


template <class T>
typename List<T>::Iterator List<T>::begin() const
{
	return Iterator(head);
}


template <class T>
typename List<T>::Iterator List<T>::end() const
{
	return Iterator(nullptr);
}