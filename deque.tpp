//Rohan J. Dani Project 4 11/20/2017 Professor Gerdes 
#include "deque.hpp"
#include <new> 
#include <stdexcept>
#include <iostream>

template <typename T>
Deque<T>::Deque() {
	itemCount = 0;
	headptr = nullptr; 
	tailptr = nullptr;
}

template <typename T>
Deque<T>::~Deque() {
	while (isEmpty() == false) {
		popBack();
	}
	itemCount = 0;
	headptr = nullptr;
	tailptr = nullptr;
}

template <typename T>
Deque<T>::Deque(const Deque<T>& Copy)
{
	//Node<T> *newPtr;
	//itemCount = Copy.itemCount;
	itemCount = 0;
	Node<T>* originalPtr = Copy.headptr;
	if (originalPtr == nullptr) {
		headptr = nullptr;
		tailptr = nullptr;
	}
	else {
		/*headptr = new Node<T>();
		tailptr = headptr;*/
	//	headptr->setItem(originalPtr->getItem());
		//newPtr = headptr;
//		originalPtr = originalPtr->getNext();

		while (originalPtr != nullptr) {

			T nextItem = originalPtr->getItem();
			//Node<T>* newNodePtr = new Node<T>(nextItem);

			//if (newNodePtr != nullptr) {
				this->pushBack(nextItem);
				originalPtr = originalPtr->getNext();

				/*newPtr->setNext(newNodePtr);
				newPtr = newPtr->getNext();
				originalPtr = originalPtr->getNext();*/

			}

		}
		//newPtr->setNext(nullptr);
		//::cout << "done";
	}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T> &Copy) {
	//Node<T> *newPtr;
	while (headptr != nullptr) {
		this->popBack();
	}
	//itemCount = Copy.itemCount;
	Node<T>* originalPtr = Copy.headptr;
	if (originalPtr == nullptr) {
		headptr = nullptr;
		tailptr = nullptr;
	}
	else {
		headptr = new Node<T>();
		tailptr = headptr;
		//headptr->setItem(originalPtr->getItem());
		//newPtr = headptr;
		//originalPtr = originalPtr->getNext();

		while (originalPtr != nullptr) {

			T nextItem = originalPtr->getItem();
			//Node<T>* newNodePtr = new Node<T>(nextItem);
			this->pushBack(nextItem);
			originalPtr = originalPtr->getNext();
			/*if (newNodePtr != nullptr) {
				newPtr->setNext(newNodePtr);
				newPtr = newPtr->getNext();
				originalPtr = originalPtr->getNext();

			}*/

		}
		//newPtr->setNext(nullptr);
		return *this;
		//::cout << "done";
	}
}



template <typename T>
bool Deque<T>::isEmpty() const noexcept {
	if (itemCount == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
void Deque<T>::pushFront(const T & item) {
	Node<T> *insertNode = new Node<T>;
	if (insertNode == nullptr) {
		throw std::bad_alloc();
	}
	insertNode->setItem(item);
	if (itemCount == 0) {
		headptr = insertNode;
		headptr->setNext(nullptr);
		headptr->setPrevious(nullptr);
		tailptr = insertNode; //one item so set head and tail to the one item 
	}
	else {
		headptr->setPrevious(insertNode); //setting up underneath linkage for doubly linked list
		insertNode->setNext(headptr); //traverse both ways in deque
		insertNode->setPrevious(nullptr); //set insertNodes previous pointer to Null cause insertNode at front
		headptr = insertNode; //set headptr equal to the front which is insertNode right now 
	}
	itemCount++;
}

template <typename T>
void Deque<T>::popFront() {
	if (itemCount == 0) {
		throw std::runtime_error("deque is NULL");
	}
	Node<T> *popNode = headptr; //set popNode to front of list
	headptr = popNode->getNext(); //set headptr to node after
	if (headptr != nullptr) {
		headptr->setPrevious(nullptr); //then set previous pointer of headptr to null
	}
	delete popNode; //delete head ptr
	itemCount--;
	if (itemCount == 0)
	{
		tailptr = nullptr; //if we empty the list, make sure tailptr isn't pointing to deleted memory
	}
}

template <typename T>
T Deque<T>::front() const {
	if (itemCount == 0) {
		throw std::runtime_error("deque is NULL");
	}
	return headptr->getItem();//got item at headptr
}

template <typename T>
T Deque<T>::back() const {
	if (itemCount == 0) {
		throw std::runtime_error("deque is NULL");
	}
	return tailptr->getItem(); //got item at tailptr
} 

template <typename T>
void Deque<T>::popBack(){
	if (itemCount == 0) {
		throw std::runtime_error("deque is NULL");
	}
	Node<T> *popNode = tailptr;
	tailptr = popNode->getPrevious(); 
	if (tailptr != nullptr) {
		tailptr->setNext(nullptr);
	}
	delete popNode; //same logic as popfront
	itemCount--;
	if (itemCount == 0)
	{
		headptr = nullptr; //if list is empty, make sure headptr isn't pointing to deleted memory
	}
}

template <typename T>
void Deque<T>::pushBack(const T & item) {
	Node<T> *insertNode = new Node<T>;
	if (insertNode == nullptr) {
		std::cout << "Push back insert node is null";
		throw std::bad_alloc();
	}
	insertNode->setItem(item);
	if (itemCount == 0) {
		headptr = insertNode;
		headptr->setNext(nullptr);
		headptr->setPrevious(nullptr);
		tailptr = insertNode; //one item so set head and tail to the one item 
	}
	else {
		tailptr->setNext(insertNode);
		insertNode->setPrevious(tailptr); //same logic as pushFront but at end of deque
		insertNode->setNext(nullptr);
		tailptr = insertNode;
		//delete insertNode;
	}
	itemCount++;
}