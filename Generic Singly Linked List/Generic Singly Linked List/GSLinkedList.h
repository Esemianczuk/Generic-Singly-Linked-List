/*
Created by Eric Semianczuk on 11/11/16
Copyright (C) 2016 Eric Semianczuk.

This file is part of Generic Singly Linked List.

Generic Singly Linked List is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Generic Singly Linked List is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef GENERIC SINGLY LINKED LIST_GENERIC SINGLY LINKED LIST_GSLINKEDLIST_H
#define GENERIC SINGLY LINKED LIST_GENERIC SINGLY LINKED LIST_GSLINKEDLIST_H
#include <iostream>
#include <exception>

// Custom execption for attempting to perform non-empty list dependent functions
// on empty lists.
class ListException : public std::exception
{
public:
	const char* what() const throw()
	{
		return "Cannot perform operation on empty list";
	}
};

// Class for singly linked list data structure where nodes are created that store
// generic (templated) data and a pointer to the next link in the list.
//         1         2         3         5          5
// ex. [NULL|2]->[elem|3]->[elem|4]->[elem|4]->[elem|NULL]
// Contains various functions to maintain/manipulate list.
template <typename T>
class GSLinkedList
{
private:
	// The actual Node with data element and pointer to next node
	template <typename T>
	struct GSNode
	{
	public:
		T elem;
		GSNode<T>* next;
	};

	GSNode<T>* head;

public:
	// constructor sets head node to NULL
	GSLinkedList();
	// adds variable amount of nodes to newly constructed list with varidac template
	// (forwards to addFront function)
	template <typename... Args>
	GSLinkedList(Args&&... args);
	// copy constructor
	GSLinkedList(GSLinkedList<T>& source);
	// copy move constructor
	GSLinkedList(GSLinkedList<T>&& source);
	// assignment operator overloaded for list type
	GSLinkedList<T>& operator=(GSLinkedList<T>& source);
	// assignment move operator overloaded for list type
	GSLinkedList<T>& operator=(GSLinkedList<T>&& source);
	// addition operator overloaded to append lists
	GSLinkedList<T>& operator+(GSLinkedList<T>& source);
	// destructor cleares memory allocated by list
	~GSLinkedList();

	// Overloaded boolean operators perform operations on the AMOUNT of
	// elements in the compared lists.
	bool operator<(GSLinkedList<T>& source);
	bool operator>(GSLinkedList<T>& source);
	bool operator==(GSLinkedList<T>& source);
	bool operator!=(GSLinkedList<T>& source);

	// returns element from head node
	T& front() const;
	// returns true of list is empty
	bool empty() const;
	// adds new node to front of list with element 'e' as its data
	const T& addFront(const T& ele);
	// adds variable amount of nodes to list with variadic template
	template <typename... Args>
	const T& addFront(const T& first, const Args&... args);
	// deletes the head node and names its 'next' node as the new head
	void deleteFront();
	// prints all of the nodes in the list
	void outputAll();
	// returns amount of elements in the list
	int count();
	
};

// Constructor instantiates head node with value NULL
template <typename T>
GSLinkedList<T>::GSLinkedList() : head(NULL)
{
}
// adds variable amount of nodes to newly constructed list with varidac template
// (forwards to addFront function)
template <typename T>
template <typename... Args>
GSLinkedList<T>::GSLinkedList(Args&&... args)
{
	addFront(std::forward<Args>(args)...);
}
// Copy Constructor takes another list as the parameter 'source' then
// loops through each node and uses the 'addFront(const T& e)' to rebuild
// a new list with the copied data.
//
// Example of calling this constructor:
// GSLinkedList<int> list1 = list;
template <typename T>
GSLinkedList<T>::GSLinkedList(GSLinkedList<T>& source)
{

	GSNode<T>* temp = source.head;
	for (int i = 0; i < source.count()-1; i++)
	{
		temp = temp->next;		
	}

	for (int a = source.count()-1; a > 0; a--)
	{
		
		temp = source.head;
		for (int i = 0; i < a; i++)
		{
			
			temp = temp->next;

		}
		addFront(temp->elem);
	}

	addFront(source.head->elem);
}

// Copy Move Constructor takes an Rvalue list as the parameter 'source' then
// frees the resources of 'this' list by calling its destructor (ensures there are
// no dangling pointers). Next, it populates the 'head' node with the address of 
// the head node of the 'source' list thereby "moving" its resources.
//
// Example of calling this constructor:
// GSLinkedList<int> list1 = std::move(list);
template <typename T>
GSLinkedList<T>::GSLinkedList(GSLinkedList<T>&& source)
{
	this->~GSLinkedList();
	head = source.head;
}

// Overloaded Assignment Operator takes another list as the parameter 'source' and
// returns a ref to 'this' list (for list=list1=list2 operations).
// Assignment accomplished by first checking which list has greater size,
// if the original list contains more elements it is trimmed to the size of the 'source'
// list. If the 'source' list is larger elements are added to the original list. Next, 
// the orginial list is overwritten with the data from the source list.
//
// This is a Non-Destructive copy that leaves the original list intact, for large copies it
// is not perfered (see overloaded move assignment operator).
//
// Example of calling this overloaded operator:
// list1 = list;
template <typename T>
GSLinkedList<T>& GSLinkedList<T>::operator=(GSLinkedList<T>& source)
{
	if (this == &source)
		return *this;

	GSNode<T>* tempThis = head;
	GSNode<T>* tempSource = source.head;

	int diff = this->count() - source.count();

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			this->deleteFront();
		}
	}
	tempThis = head;

	for (int i = 0; i < source.count(); i++)
	{

		if ((tempThis->next == NULL) && (i != source.count() - 1))
		{
			GSNode<T>* newNode = new GSNode<T>;
			tempThis->next = newNode;
			newNode->next = NULL;

		}
		tempThis->elem = tempSource->elem;
		tempThis = tempThis->next;
		tempSource = tempSource->next;

	}

	return *this;
}

// Overloaded Assignment Move Operator takes an Rvalue list as the parameter 'source'
// and returns a ref to 'this' list (for list=std::move(list1)=std::move(list2) operations).
// Move is accomplished by freeing the resources to the original list and re-instantiating
// its 'head' node as the 'head' node of the 'source' list.
//
// This IS a destructive move as now both the original list and the 'source' list are pointing
// to the same memory ie. data is not copied, the resources are moved.
//
// Example of calling this overloaded operator:
// list1 = std::move(list);
template <typename T>
GSLinkedList<T>& GSLinkedList<T>::operator=(GSLinkedList<T>&& source)
{
	if (this == &source)
		return *this;

	this->~GSLinkedList();
	head = source.head;

	return *this;
}

// Overloaded addition operator takes list as the parameter 'source' and
// returns a ref to 'this' list (for list+list1+list2 operations).
// Addition is analogous to appending two lists as the 'source' list simply
// has each of its elements added to the front of the original list.
//
// Example of calling this overloaded operator:
// list1 + list;
// 'list1' now has all of the elements of 'list' added to it.
template <typename T>
GSLinkedList<T>& GSLinkedList<T>::operator+(GSLinkedList<T>& source)
{
	if (source.count() == 0)
		return *this;

	GSNode<T>* temp = source.head;

	for (int i = 0; i < source.count(); i++)
	{
		addFront(temp->elem);
		temp = temp->next;
	}

	return *this;
}
//---------------------------------------------------------------
// Overloaded boolean operators perform operations on the AMOUNT of
// elements in the compared lists.
template <typename T>
bool GSLinkedList<T>::operator<(GSLinkedList<T>& source)
{
	return this->count() < source.count();
}

template <typename T>
bool GSLinkedList<T>::operator>(GSLinkedList<T>& source)
{
	return this->count() > source.count();
}

template <typename T>
bool GSLinkedList<T>::operator==(GSLinkedList<T>& source)
{
	return this->count() == source.count();
}

template <typename T>
bool GSLinkedList<T>::operator!=(GSLinkedList<T>& source)
{
	return this->count() != source.count();
}
//---------------------------------------------------------------

// Destructor deletes the dynamically allocated nodes in the list using
// 'deleteFront()' while the list is not 'empty()'.
template <typename T>
GSLinkedList<T>::~GSLinkedList()
{
	while (!empty())
		deleteFront();
}

// Returns element of the head node in the list, throws exeception if
// list is empty.
template <typename T>
T& GSLinkedList<T>::front() const
{
	try
	{
		if (empty())
			throw ListException();
		return head->elem;
	}
	catch (ListException e)
	{
		cout << e.what();
	}
}

// Returns true if list is empty.
template <typename T>
bool GSLinkedList<T>::empty() const
{
	return head == NULL;
}

// Adds new node to list and stores the 'ele' parameter as its 'elem'.
//
// Accomplished by changing its 'next' to pointer to point to the current 
// 'head' node, then changing the 'head' pointer to point to this node.
template <typename T>
const T& GSLinkedList<T>::addFront(const T& ele)
{
	GSNode<T>* newNode = new GSNode<T>;
	newNode->elem = ele;
	newNode->next = head;
	head = newNode;
	return ele;
}

// addFront with variadic template that recursivly calls the single
// parameter addFront to add any amount of elements to the list.
//
// example of calling function:
// GSLinkedList<int> list(1,2,3,4,5);
template <typename T>
template <typename... Args>
const T& GSLinkedList<T>::addFront(const T& ele, const Args&... args)
{
	addFront(ele);
	return addFront(args...);
}

// Deletes the current 'head' node then has the 'head' node point to the
// next node in the list. 
//
// Exeception is thrown if this is attempted on an empty list.
template <typename T>
void GSLinkedList<T>::deleteFront()
{
	try
	{
		if (empty())
			throw ListException();

		GSNode<T>* oldFront = head;
		head = head->next;
		oldFront = NULL;
		delete oldFront;

	}
	catch (ListException e)
	{
		std::cout << e.what();
	}
}

// Loops through list and prints each node element.
template <typename T>
void GSLinkedList<T>::outputAll()
{
	GSNode<T>* temp = head;
	while (temp != NULL)
	{
		std::cout << temp->elem << std::endl;
		temp = temp->next;
	}
}

// Loops through list to count each element then returns
// the amount.
template <typename T>
int GSLinkedList<T>::count()
{
	GSNode<T>* temp = head;
	int count = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}
#endif