// Robin Kalia 
// robinkalia@berkeley.edu
// UC Berkeley
// 
// Queue: Library that contains implementation of different kinds of queues
// PCQueue.hpp: Contains basic implementations of Producer Consumer Queue


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRODUCERCONSUMERQUEUE_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRODUCERCONSUMERQUEUE_H

#include <iostream>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>


template<typename T>
class PCQueue {
private:
	std::vector<T> buff_;
	int32_t buffSize_;
	sem_t used_;
	sem_t free_;
	pthread_mutex_t mlock_;
	int32_t nextIn_;
	int32_t nextOut_;

public:
	PCQueue(int32_t buffer_size = 100);
	~PCQueue();

	void push(const T &elem);
	T* pop();
};


template<typename T>
PCQueue<T>::PCQueue(int32_t buffer_size) : nextIn_(0), nextOut_(0)
{
	sem_init(&used_, 0, 0);
	sem_init(&free_, 0, buffSize_);
	pthread_mutex_init(&mlock_, NULL);
	
	buffSize_ = buffer_size;
	buff_.reserve(buffSize_);
}


template<typename T>
PCQueue<T>::~PCQueue()
{
	pthread_mutex_lock(&mlock_);
	buff_.clear();
	pthread_mutex_lock(&mlock_);

	pthread_mutex_destroy(&mlock_);
	sem_destroy(&used_);
	sem_destroy(&free_);
}


template<typename T>
void PCQueue<T>::push(T &elem)
{
	sem_wait(&free_);

	pthread_mutex_lock(&mlock_);
	buff_.push_back(elem);
	nextIn_++;
	nextIn_ = (nextIn_ == buffSize_) ? 0 : nextIn_;
	pthread_mutex_unlock(&mlock_);
	
	sem_post(&used_);
}


template<typename T>
T PCQueue<T>::pop()
{
	T* elem = nullptr;

	sem_wait(&used_);

	pthread_mutex_lock(&mlock_);
	elem = buff_.back();
	buff_.pop_back();
	nextOut_++;
	nextOut_ = (nextOut_ == buffSize_) ? 0 : nextOut_;
	pthread_mutex_unlock(&mlock_);
	
	sem_post(&free_);

	return elem;
}


#endif	// _OPENSOURCE_DATASTRUCTS_ALGOS_QUEUE_PRODUCERCONSUMERQUEUE_H