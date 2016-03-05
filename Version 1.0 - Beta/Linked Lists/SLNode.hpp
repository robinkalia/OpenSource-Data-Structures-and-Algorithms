// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Linked List: Library for different versions of the Linked List
// SLNode.h: Contains the simple implementation of a node (Single-Link Node) that can be used in both Singly Linked List and Doubly Linked List.


#ifndef _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SLNODE_H
#define _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SLNODE_H

#include <iostream>
#include <stdint.h>


template <typename T>
class SLNode
{
public:
	
	SLNode();
	SLNode(const T& el, T* next = nullptr);

	~SLNode();	

	T data_;
	Node* next_;
};


template <typename T>
SLNode<T>::SLNode()
{
	this->next_ = nullptr;
}


template <typename T>
SLNode<T>::SLNode(const T& el, T* next)
{
	this->data_ = el;
	this->next_ = next;
}


template<typename T>
SLNode<T>::~SLNode()
{

}


#endif	// _OPENSOURCE_DATASTRUCTS_AND_ALGOS_LINKEDLIST_SLNODE_H