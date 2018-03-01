//Rohan J. Dani Project 4 11/20/2017 Professor Gerdes 
#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"

#ifndef NODE_HPP
#define NODE_HPP

template<class ItemType>
class Node
{
private:
	ItemType        item; // A data item
	Node<ItemType>* next; // Pointer to next node
	Node<ItemType>* prev;

public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* nextNodePtr);
	void setPrevious(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
	Node<ItemType>* getPrevious() const;
}; // end Node

   //#include "Node.cpp"

   //  Adapted from Frank M. Carrano and Timothy M. Henry.

   /** @file Node.cpp */

#include <cstddef>
   //#include "Node.hpp"

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

template<class ItemType>
void Node<ItemType>::setPrevious(Node<ItemType>* nextNodePtr) {
	prev = nextNodePtr;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
} // end getNext

template<class ItemType>
Node<ItemType>* Node<ItemType>::getPrevious() const {
	return prev;
}
#endif

template <typename T>
class Deque: public AbstractDeque<T>{

private:
	int itemCount;
	Node<T> *headptr;
	Node<T> *tailptr;
public:
	Deque();
	~Deque();
	Deque(const Deque<T>& Copy);
	Deque<T>& operator=(const Deque<T> &Copy);
	/** Returns true if the deque is empty, else false
	*/
	bool isEmpty() const noexcept;

	/** Add item to the front of the deque
	* may throw std::bad_alloc
	*/
	void pushFront(const T & item);

	/** Remove the item at the front of the deque
	* throws std::runtime_error if the deque is empty
	*/
	void popFront();

	/** Returns the item at the front of the deque
	* throws std::runtime_error if the deque is empty
	*/
	T front() const;

	/** Add item to the back of the deque
	* may throw std::bad_alloc
	*/
	void pushBack(const T & item);

	/** Remove the item at the back of the deque
	* throws std::runtime_error if the deque is empty
	*/
	void popBack();


	/** Returns the item at the back of the deque
	* throws std::runtime_error if the deque is empty
	*/
	T back() const;

};



#include "deque.tpp"
#endif
