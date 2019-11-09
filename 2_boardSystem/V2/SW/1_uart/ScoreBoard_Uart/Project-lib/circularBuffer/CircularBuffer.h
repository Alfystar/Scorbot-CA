/*
 * CircularBuffer.h
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#ifndef PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_
#define PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_
#include "Arduino.h"
#include "../../HW_rename.h"
template<class T> class CircularBuffer {
	public:
		CircularBuffer(T buf[], size_t size);

    int put(T item);        //return new head
    int put(T *item);    //take obj pointer and copy in internal buffer, return new head
    int put(T *item, size_t len);    //take obj pointer and copy in internal buffer, return new head
    int put_externalWrite();    //return old head

    T get();
    size_t get_externalRead();    //return new tail

		T readTail();
		T readHead();
		T* getPtr();
		size_t getHead();
    T *getHeadPtr();

		size_t getTail();
    T *getTailPtr();
    void
    writeMemOut(T *mem, size_t mytail, size_t len);    //salvano in una mem i valori partendo da mytail --> mytail+len
		void reset();
    bool empty() const;    //true if empty
		bool full() const;
		size_t capacity() const;
		size_t size() const;

	private:
		T *buf_;
    int head_;
    int tail_;
    const int max_size_;
		bool full_ = 0;
};

template<class T>
CircularBuffer<T>::CircularBuffer(T buf[], size_t nElem):
        max_size_(nElem) {
    this->buf_ = buf;
    this->head_ = 0;
    this->tail_ = 0;
    //this->max_size_=nElem;

    /*
    Db.print("max_size_=");
    Db.println(max_size_);

    Db.println("cb mem:");
            for(int i=0;i<nElem;i++)
            {
                Db.flush();
                Db.print("cb mem[");
                Db.print(i);
                Db.print("]=");
                Db.println((unsigned int)&this->buf_[i]);
                delay(10);
            }
     */
}

template<class T>
void CircularBuffer<T>::reset() {
    this->head_ = this->tail_;
    this->full_ = false;
}

template<class T>
inline bool CircularBuffer<T>::empty() const {
    //if head and tail are equal, we are empty
    return (!full_ && (head_ == tail_));    //true if empty
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
void CircularBuffer<T>::writeMemOut(T *mem, size_t mytail, size_t len) {
    for (size_t i = 0; i < len; i++) {
        mem[i] = buf_[(mytail + i) % max_size_];
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
int CircularBuffer<T>::put(T item) {
    buf_[head_] = item;
    return this->put_externalWrite(); //old head
}

template<class T>
int CircularBuffer<T>::put(T *item) {
    memcpy((void *) &buf_[head_], &item, sizeof(T));
    return this->put_externalWrite(); //old head
}

template<class T>
int CircularBuffer<T>::put(T *item, size_t len) {
    memcpy((void *) &buf_[head_], &item, len);
    return this->put_externalWrite(); //old head
}

template<class T>
int CircularBuffer<T>::put_externalWrite() {
    int oldHead = this->head_;
    if (this->full_) {
        this->tail_ = (this->tail_ + 1) % this->max_size_;
    }
    this->head_ = (this->head_ + 1) % this->max_size_;
    this->full_ = (this->head_ == this->tail_);
    return oldHead; //old head
}


template<class T>
T CircularBuffer<T>::get() {
    if (empty()) {
        return T();
    }

    //Read data and advance the tail (we now have a free space)
    auto val = buf_[tail_];
    this->get_externalRead();
    return val;
}

template<class T>
T* CircularBuffer<T>::getPtr() {
    if (empty()) {
        return nullptr;
    }
    //Read data and advance the tail (we now have a free space)
    get_externalRead();
    return getTailPtr();
}

template<class T>
size_t CircularBuffer<T>::get_externalRead() {
    full_ = false;
    tail_ = (tail_ + 1) % max_size_;
    return tail_;
}

template<class T>
inline size_t CircularBuffer<T>::getHead() {
    return head_;
}

template<class T>
inline T *CircularBuffer<T>::getHeadPtr() {
    return &buf_[head_];
}

template<class T>
inline size_t CircularBuffer<T>::getTail() {
    return tail_;
}

template<class T>
inline T *CircularBuffer<T>::getTailPtr() {
    return &buf_[tail_];
}

#endif /* PROJECT_LIB_CIRCULARBUFFER_CIRCULARBUFFER_H_ */
