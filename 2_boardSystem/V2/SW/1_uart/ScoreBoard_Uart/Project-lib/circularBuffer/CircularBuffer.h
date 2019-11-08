/*
 * CircularBuffer.h
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#ifndef PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_
#define PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_
#include "Arduino.h"

template<class T> class CircularBuffer {
	public:
		CircularBuffer(T buf[], size_t size);

		size_t put(T item);	//return new head
		size_t put_externalWrite();	//return new head
		T readTail();
		T readHead();
		T get();
		T* getPtr();
		size_t getHead();
		size_t getTail();
		void writeMem(T* mem, size_t tail, size_t len);	//salvano in mem i valori partendo da tail --> head
		void reset();
		bool empty() const;
		bool full() const;
		size_t capacity() const;
		size_t size() const;

	private:
		T *buf_;
		size_t head_ = 0;
		size_t tail_ = 0;
		const size_t max_size_;
		bool full_ = 0;
};

template<class T>
CircularBuffer<T>::CircularBuffer(T buf[], size_t nElem) :
		max_size_(nElem * sizeof(buf[0])) {
	this->buf_ = buf;
}

template<class T>
void CircularBuffer<T>::reset() {
	this->head_ = this->tail_;
	this->full_ = false;
}

template<class T>
inline bool CircularBuffer<T>::empty() const {
	//if head and tail are equal, we are empty
	return (!full_ && (head_ == tail_));
}

template<class T>
inline bool CircularBuffer<T>::full() const {
	//If tail is ahead the head by 1, we are full
	return full_;
}

template<class T>
inline size_t CircularBuffer<T>::capacity() const {
	return max_size_;
}

template<class T>
inline T CircularBuffer<T>::readTail() {
	return this->buf_[tail_];
}

template<class T>
inline T CircularBuffer<T>::readHead() {
	return this->buf_[head_];
}

template<class T>
void CircularBuffer<T>::writeMem(T* mem, size_t tail, size_t len) {

	for (size_t i = 0; i < len; i++) {
		mem[i] = buf_[(tail + i) % max_size_];
	}
	full_ = false;
}

template<class T>
size_t CircularBuffer<T>::size() const {
	size_t size = max_size_;

	if (!full_) {
		if (head_ >= tail_) {
			size = head_ - tail_;
		} else {
			size = max_size_ + head_ - tail_;
		}
	}

	return size;
}

template<class T>
size_t CircularBuffer<T>::put(T item) {
	size_t oldHead = head_;
	buf_[head_] = item;

	if (full_) {
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
	return oldHead; //old head
}

template<class T>
size_t CircularBuffer<T>::put_externalWrite() {
	size_t oldHead = head_;

	if (full_) {
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
	return oldHead; //old head
}


template<class T>
T CircularBuffer<T>::get() {
	if (empty()) {
		return T();
	}

	//Read data and advance the tail (we now have a free space)
	auto val = buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}


template<class T>
T* CircularBuffer<T>::getPtr() {
	if (empty()) {
		return nullptr;
	}

	//Read data and advance the tail (we now have a free space)
	auto val = &buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}
template<class T>
inline size_t CircularBuffer<T>::getHead() {
	return head_;
}

template<class T>
inline size_t CircularBuffer<T>::getTail() {
	return tail_;
}

#endif /* PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_ */
