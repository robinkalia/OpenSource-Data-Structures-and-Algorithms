// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Linked List: Library for different versions of the Linked List
// SinglyLinkedList.h: Contains the simple implementation of Singly Linked List.


#ifndef _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SINGLYLINKED_LIST_H 
#define _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SINGLYLINKED_LIST_H

#include <iostream>
#include <stdint.h>

#include "SLNode.hpp"


template<typename T>
class SinglyLinkedList
{
private:
	SLNode<T> *head_, *tail_;

public:

	SinglyLinkedList();
	~SinglyLinkedList();

	void AddElementToHead(const T& el);
	void AddElementToTail(const T& el);
	
	T DeleteFromHead();
	T DeleteFromTail();

	void DeleteNode(const T& el);
	
	bool IsInList(const T& el) const;
	bool IsEmpty() const;
};


template<typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head_ = tail_ = nullptr;
}


template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	if ((head_ == nullptr)&&(tail_ == nullptr))	return;
	else {
		if (head_ == tail_)	{
			delete head_;
			head_ = tail_ = nullptr;
			return;
		}

		SLNode<T> current_node = head_;
		while (current_node != nullptr) {
			current_node = head_->next_;
			delete head_;
			head_ = current_node;
		}
		
		head_ = tail_ = nullptr;
		return;
	}
}


template<typename T>
void SinglyLinkedList<T>::AddElementToHead(const T& el)
{
	if (this->IsEmpty())	{
		head_ = tail_ = new SLNode<T>(el);
	} else {
		SLNode<T> new_node = new SLNode<T>(el);

		new_node->next_ = head_;
		head_ = new_node;
	}
}


template<typename T>
void SinglyLinkedList<T>::AddElementToTail(const T& el)
{
	if (this->IsEmpty())
		head_ = tail_ = new SLNode<T>(el);
	} else {
		SLNode<T> new_node = new SLNode<T>(el);
		tail_->next_ = new_node;
		tail_ = new_node;
	}
}


template<typename T>	
T SinglyLinkedList<T>::DeleteFromHead()
{
	if (this->IsEmpty())	{
		std::exception ex("Empty Singly-Linked List: Cannot access the head node element");
		throw ex;
	}

	T el = head_->data_;

	SLNode<T> current_node = head_->next_;
	delete head_;
	head_ = current_node;

	return el;
}


template<typename T>
T SinglyLinkedList<T>::DeleteFromTail()
{
	if (this->IsEmpty())	{
		std::exception ex("Empty Singly-Linked List: Cannot access the tail node element");
		throw ex;
	}

	T el = tail_->data_;

   	if (head_ == tail_)	{
    		delete head_;
    		head_ = tail_ = nullptr;
    		return el;
    	}

	SLNode<T> current_node = head_;
	while (current_node->next_ != tail_)	current_node = current_node->next_;
	delete tail_;
	tail_ = current_node;
	tail_->next_ = nullptr;

	return el;
}


template <typename T>
void SinglyLinkedList<T>::DeleteNode(const T& el)
{
	if (this->IsEmpty())	return;

	while (head_->data_ == el)	{
		DeleteFromHead();
		if (this->IsEmpty())	return;
	}

	if (head_ == tail_) return;

	SLNode<T> prev_node = head_;
	SLNode<T> current_node = prev_node->next_;
	
	do  {
		if (current_node->data_ == el)	{
			prev_node->next_ = current_node->next_;
			delete current_node;
			current_node = prev_node->next_;
		} else {
			prev_node = current_node;
			current_node = current_node->next_;
		}
		
	} while (current_node != nullptr);
}


template<typename T>	
bool SinglyLinkedList<T>::IsInList(const T& el) const
{
	if (this->IsEmpty())	return false;
	
	SLNode<T> current_node = head_;
	while (current_node != nullptr) {
		if (current_node->data_ == el)	return true;
		current_node = current_node->next_;
	}

	return false;
}


template<typename T>
bool SinglyLinkedList<T>::IsEmpty() const
{
	if ((head_ == nullptr)&&(tail_ = nullptr))	return true;
	else return false;
}


#endif		// _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SINGLYLINKED_LIST_H
