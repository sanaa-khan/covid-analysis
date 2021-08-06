#include <iostream>
using namespace std;

template <typename T>
class Vector {
private:
	T* ptr;
	int size_;
	int c_index;
	int cap;

public:
	Vector() : ptr(NULL), size_(-1), c_index(0), cap(0) {};

	Vector(int size) : size_(0), c_index(0), cap(size) {
		ptr = new T[cap];
	}

	Vector(int size, const T& iv) : size_(size), c_index(size_) {
		ptr = new T[size_];

		for (int i = 0; i < size_; i++)
			ptr[i] = iv;
	}

	Vector(const Vector<T>& obj) : size_(obj.size_), c_index(obj.c_index), cap(obj.cap) {
		ptr = new T[cap];

		for (int i = 0; i < size_; i++)
			ptr[i] = obj.ptr[i];
	}

	~Vector() {
		delete[]ptr;
	}

	const T& operator = (const T& obj) {

		if (size_ == cap) {
			Vector<T> copy(*this);
			~*this;

			cap *= 2;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy.ptr[i];

			delete[]copy.ptr;
		}

		size_++;
		ptr[size_] = obj;
		return ptr[size_];
	}

	T* begin() {
		return ptr;
	}

	T* end() {
		return (ptr + size_ - 1);
	}

	int size() {
		return size_;
	}

	void resize(int x) {
		if (x == cap)
			return;

		else if (x > cap) {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}

		else {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			if (size_ > cap)
				size_ = cap;

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}
	}

	bool empty() {
		if (size_ == -1)
			return true;

		return false;
	}

	void shrink_to_fit(int x) {

		Vector<T> copy(*this);
		delete[]ptr;

		cap = x;
		ptr = new T[cap];

		if (size_ > cap)
			size_ = cap;

		for (int i = 0; i < size_; i++)
			ptr[i] = copy[i];

		delete[]copy.ptr;
	}

	T& operator [] (int index) {
		return ptr[index];
	}

	T& front() {
		return ptr[0];
	}

	T& back() {
		return ptr[size_ - 1];
	}

	void push_back(const T& value) {

		if (size_ == cap)
			this->resize(cap * 2);

		ptr[size_] = value;
		size_++;
	}

	void pop_back() {
		size_--;
	}

	void swap(Vector<T>& other) {
		Vector<T> temp(*this);
		delete[]ptr;

		cap = other.cap;
		size_ = other.size_;
		c_index = other.c_index;
		ptr = new T[cap];

		for (int i = 0; i < size_; i++)
			ptr[i] = other.ptr[i];

		delete[]other.ptr;

		other.size_ = temp.size_;
		other.c_index = temp.c_index;
		other.cap = temp.cap;
		other.ptr = new T[other.cap];

		for (int i = 0; i < other.size_; i++)
			other.ptr[i] = temp.ptr[i];

		delete[]temp.ptr;
	}

	void clear() {
		//c_index = 0;
		size_ = -1;
	}

	int capacity() {
		return cap;
	}
};
