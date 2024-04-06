#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <exception>
using namespace std;

#define   PROBLEM_1_QUEUE_H   1
#define   PROBLEM_2_QUEUE_H   2
#define   PROBLEM_3_QUEUE_H   3

template<typename T>
class Node{
	public:
		template<typename T_queue>
		friend class Queue;

		// big 3
		Node();
		Node(const Node<T> &in);
		Node<T> operator= (const Node<T> &in);

	private:
		T value;
		Node<T> *next;

};

template<typename T>
Node<T>::Node(){
	next = nullptr;
}

template<typename T>
Node<T>::Node(const Node<T> &in){
	value = in.value;
	next = in.next;
}

template<typename T>
Node<T> Node<T>::operator= (const Node<T> &in){
	value = in.value;
	next = in.next;

	return *this;
}

// start making Queue

template<typename T>
class Queue{
	public:
		//big 3
		Queue();
		Queue(const Queue<T> &in);
		Queue<T> operator= (const Queue<T> &in);

		~Queue();

		void enqueue(const T &in_v);
		T dequeue();

		int get_Data_num() const;

	private:
		Node<T> *head;
		Node<T> *tail;
		int data_num;

};

template<typename T>
Queue<T>::Queue(){
	head = nullptr;
	tail = nullptr;
	data_num = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T> &in){
	head = nullptr;
	tail = nullptr;
	data_num = 0;
	Node<T> *temp = in.head;

	while(temp != nullptr){
		enqueue(temp->value);
		temp = temp->next;
	}
}

template<typename T>
Queue<T>::~Queue(){
	if(head != nullptr){
		Node<T> *kill;

		while(head != nullptr){
			kill = head;
			head = head->next;
			delete kill;
		}
	}
}

template<typename T>
Queue<T> Queue<T>::operator= (const Queue<T> &in){
	if(head != nullptr){
		// clean the original Queue first
		Node<T> *temp = head;
		Node<T> *kill;

		while(temp != nullptr){
			kill = temp;
			temp = temp->next;
			delete kill;
		}
	}

	head = nullptr;
	tail = nullptr;
	data_num = 0;
	Node<T> *temp = in.head;

	while(temp != nullptr){
		enqueue(temp->value);
		temp = temp->next;
	}

	return *this;
}

template<typename T>
int Queue<T>::get_Data_num() const {
	return data_num;
}

template<typename T>
void Queue<T>::enqueue(const T &in_v){
	if(head == nullptr){  // adding the first data
		if(tail != nullptr){
			throw PROBLEM_1_QUEUE_H;
		}

		head = new Node<T>;
		if(head == nullptr){
			throw PROBLEM_2_QUEUE_H;
		}
		head->value = in_v;
		head->next = nullptr;  // double ensure that next is nullptr
		tail = head;
	}else{   //  not the first data, append to the end
		if( (tail == nullptr) || (tail->next != nullptr) ){
			throw PROBLEM_1_QUEUE_H;
		}

		Node<T> *temp;

		temp = new Node<T>;
		if(temp == nullptr){
			throw PROBLEM_2_QUEUE_H;
		}
		temp->value = in_v;
		temp->next = nullptr;  // double ensure the next is nullptr
		tail->next = temp;
		tail = temp;
	}

	data_num ++;
}

template<typename T>
T Queue<T>::dequeue(){
	if(head == nullptr){  // nothing to dequeue
		throw PROBLEM_3_QUEUE_H;
	}else{
		if(tail->next != nullptr){
			throw PROBLEM_1_QUEUE_H;
		}
	}

	Node<T> *kill = head;
	T result = head->value;
	head = head->next;
	delete kill;
	if(head == nullptr){  // become Empty
		tail = nullptr;
	}

	return result;
}

#endif
