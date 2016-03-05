// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Linked List: Library for different versions of the Linked List
// DoublyLinkedList.h: Contains the simple implementation of Doubly Linked List.


#ifndef _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DOUBLYLINKED_LIST_H 
#define _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DOUBLYLINKED_LIST_H

#include <iostream>
#include <stdint.h>

#include "DLNode.hpp"


template<typename T>
class DoublyLinkedList
{
private:
	DLNode<T> *head_, *tail_;

public:

	DoublyLinkedList();
	~DoublyLinkedList();

	void AddElementToHead(const T& el);
	void AddElementToTail(const T& el);
	
	T DeleteFromHead();
	T DeleteFromTail();

	void DeleteNode(const T& el);
	
	bool IsInList(const T& el) const;
	bool IsEmpty() const;
};


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	head_ = tail_ = nullptr;
}


template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	if ((head_ == nullptr)&&(tail_ == nullptr))	return;
	else {
		if (head_ == tail_)	{
			delete head_;
			head_ = tail_ = nullptr;
			return;
		}

		DLNode<T> current_node = head_;
		while (current_node != nullptr) {
			current_node = head_->next_;
			delete head_;
			head_ = current_node;
			head_->prev_ = nullptr;
		}
		
		head_ = tail_ = nullptr;
		return;
	}
}


template<typename T>
void DoublyLinkedList<T>::AddElementToHead(const T& el)
{
	if (this->IsEmpty())	{	
		head_ = tail_ = new DLNode<T>(el);
	} else {
		DLNode<T> new_node = new DLNode<T>(el);

		new_node->next_ = head_;
		head_->prev_ = new_node;
		head_ = new_node;
	}
}


template<typename T>
void DoublyLinkedList<T>::AddElementToTail(const T& el)
{	
	if (this->IsEmpty())	{
		head_ = tail_ = new DLNode<T>(el);
	} else {
		DLNode<T> new_node = new DLNode<T>(el);
		tail_->next_ = new_node;
		new_node->prev_ = tail_;
		tail_ = new_node;
	}
}


template<typename T>	
T DoublyLinkedList<T>::DeleteFromHead()
{
	if (this->IsEmpty())	{
		std::exception ex("Empty Doubly-Linked List: Cannot access the head node element");
		throw ex;
	}

	T el = head_->data_;

	DLNode<T> current_node = head_->next_;
	delete head_;
	head_ = current_node;
	head_->prev_ = nullptr;

	return el;
}


template<typename T>
T DoublyLinkedList<T>::DeleteFromTail()
{
	if (this->IsEmpty())	{
		std::exception ex("Empty Doubly-Linked List: Cannot access the tail node element");
		throw ex;
	}

	T el = tail_->data_;

    	if (head_ == tail_)	{
    		delete head_;
    		head_ = tail_ = nullptr;
    		return el;
    	}

	DLNode<T> current_node = tail_->prev_;	
	delete tail_;
	tail_ = current_node;
	tail_->next_ = nullptr;

	return el;
}


template <typename T>
void DoublyLinkedList<T>::DeleteNode(const T& el)
{
	if (this->IsEmpty())	return;	

	while (head_->data_ == el)	{
		DeleteFromHead();
		if (this->IsEmpty())	return;
	}

	if (head_ == tail_) return;

	DLNode<T> prev_node = head_;
	DLNode<T> current_node = prev_node->next_;
	
	do  {
		if (current_node->data_ == el)	{
			prev_node->next_ = current_node->next_;
			current_node->next_->prev_ = prev_node;
			delete current_node;
			current_node = prev_node->next_;
		} else {
			prev_node = current_node;
			current_node = current_node->next_;
		}
		
	} while (current_node != nullptr);
}


template<typename T>	
bool DoublyLinkedList<T>::IsInList(const T& el) const
{
	if (this->IsEmpty())	return false;
	
	DLNode<T> current_node = head_;
	while (current_node != nullptr) {
		if (current_node->data_ == el)	return true;
		current_node = current_node->next_;
	}

	return false;
}


template<typename T>
bool DoublyLinkedList<T>::IsEmpty() const
{
	if ((head_ == nullptr)&&(tail_ = nullptr))	return true;
	else return false;
}


#endif		// _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DOUBLYLINKED_LIST_H
