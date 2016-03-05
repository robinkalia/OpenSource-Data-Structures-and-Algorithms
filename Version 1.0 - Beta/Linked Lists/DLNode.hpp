// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Linked List: Library for different versions of the Linked List
// DLDLNode.h: Contains the simple implementation of a node (Double-Link Node) that is used in the Doubly Linked List.


#ifndef _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DLNODE_H
#define _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DLNODE_H

#include <iostream>
#include <stdint.h>


template <typename T>
class DLNode
{
public:
	DLDLNode();
	DLNode(const T& el, T* next = nullptr, T* prev = nullptr);

	~DLNode();	
	
	T data_;
	DLNode* prev_, next_;
};


template <typename T>
DLNode<T>::DLNode()
{
	this->prev_ = nullptr;
	this->next_ = nullptr;
}


template <typename T>
DLNode<T>::DLNode(const T& el, T* next, T* prev)
{
	this->data_ = el;
	this->prev_ = prev;
	this->next_ = next;
}


template<typename T>
DLNode<T>::~DLNode()
{
	
}


#endif	// _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_DLNODE_H