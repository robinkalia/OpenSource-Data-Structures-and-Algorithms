// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Queue: Library that contains implementation of different kinds of queues
// PriorityQueue.hpp: Contains various implementations of Priority Queues


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRIORITYQUEUE_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRIORITYQUEUE_H

#include <iostream>
#include <stdint.h>
#include <stdexcept>

#include <vector>
#include <tuple>


////////////////////// ABSTRACT QUEUE DATA STRUCTURE //////////////////////
template<typename T1, typename T2>
class Queue {
public:
	Queue() {}
	~Queue() {}

	virtual void push(const T1& elem, const T2& priority) = 0;
	virtual T1 pop() = 0;
};


////////////////////// HEAP QUEUE DATA STRUCTURE //////////////////////
template<typename T1, typename T2>
class HeapQueue : public Queue {
private:
	std::vector<std::pair<T1, T2> > buffer_;
	
	void MoveDown(int32_t first_id, int32_t last_id) {
		int32_t largest_id = 2 * first_id + 1;

		while (largest_id <= last_id) {
			if (buffer_[largest_id].second < buffer_[largest_id + 1].second)	++largest_id;

			if (buffer_[first_id].second < buffer_[largest_id].second)	{
				std::iter_swap(buffer_.begin() + first_id, buffer_.end() + largest_id);
				first_id = largest_id;
				largest_id = 2 * first_id + 1;
			} else largest_id = last_id + 1;
		}
	}


	void RestoreHeap()
	{
		int32_t start_id = buffer_.size()/2 - 1;
		for (int32_t i = start_id; i >= 0; ++i)		MoveDown(start_id, buffer_.size() - 1);
	}

public:
	HeapQueue() {	};
	~HeapQueue() {	
		buffer_.clear();
	}

	void push(const T1& elem, const T2& priority) {
		std::pair<T1, T2> queue_elem(elem, priority);

		if (buffer_.size() == 0)	{
			buffer_.push_back(queue_elem);
			return;
		}

		int32_t index = 0;
		while ((index < buffer_.size()) && (buffer_[index].second > queue_elem.second))	++index;
		buffer_.insert(buffer_.begin() + index, queue_elem);
	}

	T1 pop() {
		if (buffer_.size() == 0)
			throw std::runtime_error("ERROR: The Priority Queue is empty");

		T1 elem = buffer_[0].first;

		buffer_.erase(buffer_.begin());
	}
};


////////////////////// LINKED LIST QUEUE NODE DATA STRUCTURE //////////////////////
template<typename T1 = int64_t, typename T2 = int32_t>
class LLQNode {
public:
	LLQNode(const T1& elem, const T2 &priority) : next_(nullptr) {	
		this->data_		= elem;
		this->priority_ = priority;
	}

	~LLQNode() { }

	T1 data_;
	T2 priority_;
	LLQNode<T1, T2>* next_;
};


////////////////////// LINKED LIST QUEUE DATA STRUCTURE //////////////////////
template <typename T1, typename T2>
class LinkedListQueue : public Queue {
private:
	LLQNode<T1, T2>* head_;

public:
	LinkedListQueue()		{ head_ = nullptr;  }
	~LinkedListQueue() {
		if (head_ != nullptr) {
			while (head_->next_ != nullptr) {
				LLQNode<T1, T2>* temp_node = head_->next_;
				delete head_;
				head_ = temp_node;
			}

			delete head_;
			head_ = nullptr;
		}
	}

	void push(const T1& elem, const T2& priority) {
		LLQNode<T1, T2> *temp_node = new LLQNode<T1, T2>(elem, priority);

		if (head_ == nullptr)	{
			head_ = temp_node;
			return;
		}

		if (head_->priority_ < temp_node->priority_) {
			temp_node->next_ = head_;
			head_ = temp_node;
			return;
		}

		LLQNode<T1, T2>* current_node = head_;
		LLQNode<T1, T2>* next_node = current_node->next_;

		while (current_node->priority_ > temp_node->priority_)	{
			if ((next_node == nullptr) | (next_node->priority_ <= temp_node->priority_))
				break;

			current_node = next_node;
			next_node = current_node->next_;
			
		}

		current_node->next_ = temp_node;
		temp_node->next_ = next_node;
	}


	T1 pop() {
		if (head_ == nullptr)	{
			throw std::runtime_error("ERROR: The Priority Queue is empty");
		}

		T1 elem = head_->data_;

		LLQNode<T1, T2> *next_node = head_->next_;
		delete head_;
		head_ = next_node;

		return elem;
	}
};


////////////////////// MAIN PRIORITY QUEUE NODE DATA STRUCTURE //////////////////////
template <typename T1 = int64_t, typename T2 = int32_t>
class PriorityQueue {
private:
	Queue<T1, T2>* pQueue_;

public:
	PriorityQueue(int32_t flag = 0);
	~PriorityQueue();

	void push(const T1& elem, const T2& priority);
	T1 pop();
};


template <typename T1, typename T2>
PriorityQueue<T1, T2>::PriorityQueue(int32_t flag)
{
	if (flag == 0)	pQueue_ = new LinkedListQueue<T1, T2>();
	else pQueue_ = new HeapQueue<T1, T2>();
}


template <typename T1, typename T2>
void PriorityQueue<T1, T2>::push(const T1& elem, const T2& priority)
{
	pQueue_->push(elem, priority);
}


template <typename T1, typename T2>
T1 PriorityQueue<T1, T2>::pop()
{
	return pQueue_->pop();
}


#endif	// _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRIORITYQUEUE_H