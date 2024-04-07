#ifndef TSINGLYLIST_H
#define TSINGLYLIST_H

#include <cmath>
#include <map>
#include<string>

template <class T>
class List
{
	struct Node
	{
		T elem;
		Node* pPrevious;
		Node* pNext;

	};
	Node* pFirst;
	Node* last_viewed_element;
	int last_viewed_index;
	int size_of;
	void insertFirst(T elem);
	void findOfNodeByElem(T elem);
	void findOfNodeByIndex(int index);
	void insertAfter(T elem);

public:

	List();
	List(const List<T>& list);
	List(List<T>&& list);
	void insertInOrder(T elem);
	T& operator[](int index);
	void erase(int index);
	bool operator==(const List<T>& list);
	bool operator!=(const List<T>& list);
	List<T>& operator=(const List<T>& list);
	List<T>& operator=(List<T>&& list);
	int size() const;
	~List();
};

template <class T>
List<T>::List() : pFirst(nullptr), size_of(0), last_viewed_element(nullptr), last_viewed_index(-1) {}

template<class T>
List<T>::List(const List<T>& list)
{
	this->pFirst = nullptr;
	this->size_of = 0;
	for (Node* l = list.pFirst; l != nullptr; l = l->pNext)
		insertInOrder(l->elem);
}

template<class T>
List<T>::List(List<T>&& list)
{
	this->size_of = list.size_of;
	this->last_viewed_index = list.last_viewed_index;
	this->pFirst = list.pFirst;
	this->last_viewed_element = list.last_viewed_element;
	list.pFirst = nullptr;
	list.last_viewed_element = nullptr;
}
;

template <class T>
void List<T>::insertFirst(T elem)
{
	size_of++;
	pFirst = new Node{ elem, nullptr, pFirst };
	if (pFirst->pNext != nullptr)
		pFirst->pNext->pPrevious = pFirst;
	last_viewed_element = pFirst;
	last_viewed_index = 0;
}

template<class T>
void List<T>::findOfNodeByElem(T elem)
{
	if ((last_viewed_element != nullptr) && (last_viewed_element->elem == elem))
		return;
	if (elem < last_viewed_element->elem)
	{
		last_viewed_element = pFirst;
		last_viewed_index = 0;
	}
	for (; (last_viewed_element->pNext != nullptr) && (last_viewed_element->elem < elem);
		last_viewed_index++, last_viewed_element = last_viewed_element->pNext);
	if (last_viewed_element->elem > elem)
	{
		last_viewed_element = last_viewed_element->pPrevious;
	}
	return;
}

template<class T>
void List<T>::findOfNodeByIndex(int index)
{
	if ((index >= this->size()) || (index < 0))
		throw "Incorrect index";
	if (index == last_viewed_index)
		return;
	if (index < abs(last_viewed_index - index))
	{
		last_viewed_element = pFirst;
		last_viewed_index = 0;
	}
	else if (index < last_viewed_index)
	{
		for (; last_viewed_index != index; last_viewed_index--, last_viewed_element = last_viewed_element->pPrevious);
		return;
	}
	for (; last_viewed_index != index; last_viewed_index++, last_viewed_element = last_viewed_element->pNext);
	return;
}

template <class T>
void List<T>::insertInOrder(T elem)
{
	if ((pFirst == nullptr) || (pFirst->elem > elem))
	{
		insertFirst(elem);
		return;
	}
	findOfNodeByElem(elem);
	if (last_viewed_element->elem == elem)
		last_viewed_element->elem += elem;
	else
		insertAfter(elem);
	return;
}

template <class T>
void List<T>::insertAfter(T elem)
{
	size_of++;
	last_viewed_element->pNext = new Node{ elem, last_viewed_element, last_viewed_element->pNext };
	if (last_viewed_element->pNext->pNext != nullptr)
		last_viewed_element->pNext->pNext->pPrevious = last_viewed_element->pNext;
}

template<class T>
void List<T>::erase(int index)
{
	findOfNodeByIndex(index);
	Node* pDel = last_viewed_element;
	if (size_of == 1)
	{
		pFirst = nullptr;
		delete last_viewed_element;
	}
	else if (index != size_of - 1)
	{
		last_viewed_element = last_viewed_element->pNext;
		last_viewed_element->pPrevious = pDel->pPrevious;
		if (index != 0)
			pDel->pPrevious->pNext = pDel->pNext;
		else
			pFirst = last_viewed_element;
		delete pDel;
	}
	else
	{
		last_viewed_element = last_viewed_element->pPrevious;
		last_viewed_element->pNext = pDel->pNext;
		delete pDel;
	}
	//last_viewed_index--;
	size_of--;
	return;
}

template<class T>
bool List<T>::operator==(const List<T>& list)
{
	if (this->size_of != list.size_of)
		return false;
	Node* p1 = this->pFirst;
	Node* p2 = list.pFirst;
	for (; p1 != nullptr; p1 = p1->pNext, p2 = p2->pNext)
		if (p1->elem != p2->elem)
			return false;
	return true;
}

template<class T>
bool List<T>::operator!=(const List<T>& list)
{
	return (!(*this == list));
}

template<class T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (*this == list)
		return *this;
	for (Node* p = pFirst; p != nullptr;)
	{
		Node* pDel = p;
		p = p->pNext;
		delete pDel;
	}
	pFirst = nullptr;
	this->size_of = 0;
	insertFirst(list.pFirst->elem);
	for (Node* l = list.pFirst->pNext; l != nullptr; l = l->pNext)
		insertInOrder(l->elem);
	return *this;
}

template<class T>
List<T>& List<T>::operator=(List<T>&& list)
{
	for (Node* p = pFirst; p != nullptr;)
	{
		Node* pDel = p;
		p = p->pNext;
		delete pDel;
	}
	this->size_of = list.size_of;
	this->last_viewed_index = list.last_viewed_index;
	this->pFirst = list.pFirst;
	this->last_viewed_element = list.last_viewed_element;
	list.pFirst = nullptr;
	list.last_viewed_element = nullptr;
	return *this;
}

template<class T>
int List<T>::size() const
{
	return size_of;
}

template <class T>
T& List<T>::operator[](int index)
{
	if (index >= size_of)
		throw "Incorrect index";
	findOfNodeByIndex(index);
	return last_viewed_element->elem;
}

template <class T>
List<T>::~List()
{
	for (Node* p = pFirst; p != nullptr;)
	{
		Node* pDel = p;
		p = p->pNext;
		delete pDel;
	}
}

#endif // TSINGLYLIST_H