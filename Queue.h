#pragma once

#include <iostream>
#include <string>
using std::cout;
using std::string;

template <class DT>
class Queue {

	template <class DT>
	struct node {
		DT data;
		node* next;
	};

	node<DT>* front;
	node<DT>* rear;
	int size;

public:

	Queue() : front(NULL), rear(NULL), size(0) {}

	~Queue() {

		node<DT>* current = front;

		while (front != NULL) {
			current = front;
			front = front->next;
			delete current;
		}
	}

	void enqueue(const DT& newDataItem) {
		node<DT>* temp;
		temp = new node<DT>;
		temp->data = newDataItem;
		temp->next = NULL;

		if (isEmpty()) {
			front = temp;
			rear = temp;
		}

		else {
			rear->next = temp;
			rear = rear->next;
		}

		size++;
	}

	DT dequeue() {

		if (isEmpty())
			return 0;

		DT val = front->data;
		node<DT>* temp;
		temp = front;
		front = front->next;
		delete temp;

		size--;

		return val;
	}

	void clear() {

		node<DT>* temp = front;

		while (temp != rear) {
			temp->data = -1;
			temp = temp->next;
		}

		size = 0;
	}

	bool isEmpty() const {

		if (!size)
			return true;

		return false;
	}

	void operator + (const DT& x) {
		this->enqueue(x);
	}

	DT operator --() {
		DT val = this->dequeue();
		return val;
	}

	void display() {
		node<DT>* temp = front;

		while (temp != NULL) {
			cout << temp->data;
			temp = temp->next;
		}

		cout << "\n";
	}

	int getLength() {
		return size;
	}

	int operation(char ch) {

		if (ch == 'E') {
			return (this->isEmpty());
		}

		if (ch == 'C') {
			this->clear();
			return 0;
		}

		if (ch == '#')
			return this->getLength();

		if (ch == 'Q')
			exit(0);
	}

	void queueString(string str) {

		int spc = 0; // counting words (word = spc + 1)
		int len = 0;

		while (str[len] != '\0') {

			if (str[len] == 32)
				spc++;

			len++;
		}

		cout << "\n" << len << "\n";

		Queue<char>* arr = new Queue<char>[spc + 1]; // no of words

		int index = 0;

		for (int i = 0; i < len; i++) {

			arr[index].enqueue(str[i]);

			if (str[i] == 32)
				index++; // moves to next queue when space is encountered
		}

		// displaying individually

		for (int i = 0; i < spc + 1; i++)
			arr[i].display();

		cout << "\n";

		// moving all queues into one queue

		index = 0;

		for (int i = 0; i < len; i++) {

			char ch = arr[index].dequeue();

			this->enqueue(ch);

			if (ch == 32)
				index++; // moves to next queue when space is encountered
		}

		this->display(); 
	}

};