#include<iostream>
#include<algorithm>
#include"Circular_Buffer.h"


CircularBuffer::CircularBuffer() {
	buffer = nullptr;
	_capacity = 0;
	_size = 0;
	_idx_head = 0;
	_idx_end = 0;
	isfull = false;
}
CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}
CircularBuffer::CircularBuffer(const CircularBuffer & cb) {
	buffer = new value_type[cb._capacity];
	buffer = cb.buffer;
	_capacity = cb._capacity;
	_size = cb._size;
	_idx_head = cb._idx_head;
	_idx_end = cb._idx_end;
	isfull = cb.isfull;

	std::copy(cb.buffer, cb.buffer + cb._size, buffer);
}

CircularBuffer::CircularBuffer(int capacity) {
	if (capacity < 0) {
    	throw std::invalid_argument("Capacity must be non-negative");
	}

	buffer = new value_type[capacity];
	_capacity = capacity;
	_size = 0;
	_idx_head = 0;
	_idx_end = 0;
	isfull = false;
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem) {
	buffer = new value_type[capacity];
	_capacity = capacity;
	_size = capacity;
	_idx_head = 0;
	_idx_end = _size % _capacity;

	for(int i = 0; i < _capacity; i++) {
		buffer[i] = elem;
	}

	isfull = true;

}

value_type& CircularBuffer::operator[](int i) {
	return buffer[(_idx_head + i) % _capacity];
}
const value_type& CircularBuffer::operator[](int i) const {
	return buffer[(_idx_head + i) % _capacity];
}

value_type& CircularBuffer::at(int i) {
	if (i < 0 || i >= _size) {
		throw std::out_of_range("Index out of range");
	}
	return buffer[i];
}
const value_type& CircularBuffer::at(int i) const {
	if (i < 0 || i >= _size) {
		throw std::out_of_range("Index out of range");
	}
	return buffer[i];
}

value_type& CircularBuffer::front() {
	if(empty()) {
		throw std::out_of_range("Buffer is empty");
	}
	return buffer[_idx_head];
}

const value_type& CircularBuffer::front() const {
	if(empty()) {
		throw std::out_of_range("Buffer is empty");
	}
	return _idx_head;
}

value_type& CircularBuffer::back() {
	if (empty()) {
		throw std::out_of_range("Buffer is empty");
	}
	
	return buffer[(_idx_end - 1 + _capacity) % _capacity];
}

const value_type& CircularBuffer::back() const {
	if (empty()) {
		throw std::out_of_range("Buffer is empty");
	}


	return buffer[(_idx_end - 1 + _capacity) % _capacity];
}

value_type* CircularBuffer::linearize() {
	if (!is_linearized()) {
		std::rotate(buffer, buffer + _idx_head, buffer + _capacity);
		_idx_head = 0;
		_idx_end = _size;
    }
	return buffer;
}

bool CircularBuffer::is_linearized() const {
	return (_size == 0) || (_idx_head <= _idx_end);
}

void CircularBuffer::rotate(int new_begin) {
	if (new_begin < 0 || new_begin >= _size) {
		throw std::out_of_range("Invalid rotation index");
	}
	_idx_head = (_idx_head + new_begin) % _capacity;
	_idx_end = (_idx_end + new_begin) % _capacity;
}

int CircularBuffer::size() const {
	return _size;
}

bool CircularBuffer::empty() const {
	return _size == 0;
}

bool CircularBuffer::full() const {
	return _size == _capacity;
}

int CircularBuffer::reserve() const {
	return _capacity - _size;
}

int CircularBuffer::capacity() const {
	return _capacity;
}

void CircularBuffer::set_capacity(int new_capacity) {
	if (new_capacity < _size) {
		throw std::invalid_argument("New capacity is less than the current size");
	}
	value_type* new_buffer = new value_type[new_capacity];
	int current_idx = _idx_head;
	for (int i = 0; i < _size; ++i) {
		new_buffer[i] = buffer[current_idx];
		current_idx = (current_idx + 1) % _capacity; 
	}
	delete[] buffer;
	buffer = new_buffer;
	_capacity = new_capacity;
	_idx_head = 0;
	_idx_end = _size;
	isfull = (_size == _capacity);
}

void CircularBuffer::resize(int new_size, const value_type& item) {
	if (new_size > _capacity) {
		set_capacity(new_size);
	}
	for (int i = _size; i < new_size; ++i) {
		push_back(item);
	}
	_size = new_size;
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
	if (this != &cb) {
		delete[] buffer;
		_capacity = cb._capacity;
		_size = cb._size;
		_idx_head = cb._idx_head;
		_idx_end = cb._idx_end;
		buffer = new value_type[_capacity];
		std::copy(cb.buffer, cb.buffer + _capacity, buffer);
	}
	return *this;
}

void CircularBuffer::swap(CircularBuffer& cb) {
	std::swap(buffer, cb.buffer);
	std::swap(_capacity, cb._capacity);
	std::swap(_size, cb._size);
	std::swap(_idx_head, cb._idx_head);
	std::swap(_idx_end, cb._idx_end);
}

void CircularBuffer::push_back(const value_type& item) {
	if (full()) {
		pop_front();
	}
	buffer[_idx_end] = item;
	_size++;
	_idx_end = (_idx_end + 1) % _capacity;
	isfull = full();
}

void CircularBuffer::push_front(const value_type& item) {
	if (full()) {
		pop_back();
	}
	_idx_head = (_idx_head - 1 + _capacity) % _capacity;
	buffer[_idx_head] = item; 
	_size++;
	isfull = (_size == _capacity);
}

void CircularBuffer::pop_back() {
	if (empty()) {
		throw std::out_of_range("Buffer is empty");
	}
	_idx_end = (_idx_end - 1 + _capacity) % _capacity;
	_size--;
	isfull = false;
}

void CircularBuffer::pop_front() {
	if (empty()) {
		throw std::out_of_range("Buffer is empty");
	}

	_idx_head = (_idx_head + 1) % _capacity;
	_size--;
	isfull = false;

}

void CircularBuffer::insert(int pos, const value_type& item){
	if (pos > _size || pos < 0) {
		throw std::out_of_range("Bad pos!");
	}
	if (full()) {
		pop_front();
	}
	for (int i = _size - 1; i >= pos; --i) {
		buffer[(_idx_end - 1 + i) % _capacity] = buffer[(_idx_end + i) % _capacity];
	}

	buffer[(_idx_end + pos) % _capacity] = item;
	_size++;
}

void CircularBuffer::erase(int first, int last) {
	if (first >= last || first < 0 || last > _size) {
		throw std::out_of_range("Index out of range");
	}
	if (_size == 0) {
		throw std::out_of_range("Buffer is empty, cannot delete elems");
	}
	int count = last - first;
	for (int i = first; i < _size - count; i++) {
		buffer[(_idx_head + i) % _capacity] = buffer[(_idx_head + i + count) % _capacity];
	}
	_size -= count;
	_idx_end = (_idx_end - count + _capacity) % _capacity; 
	isfull = (_size == _capacity); 
}

void CircularBuffer::clear() {
	if (empty()) {
		throw std::underflow_error("Buffer is empty already");
	}
	_size = 0;
	_idx_head = 0;
	_idx_end = 0;
	isfull = false;

}

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
	if (a.size() != b.size()) return false;

	int j = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
	return !(a == b);
}
