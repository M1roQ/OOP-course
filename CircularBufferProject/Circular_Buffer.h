#pragma once
#include <iostream>

typedef int value_type;

class CircularBuffer {
	value_type* buffer;	// Pointer to the internal buffer array
	int _capacity;		// Total capacity of the buffer
	int _size;			// Current number of elements in the buffer
	int _idx_head;		// Index of the first element (head) in the buffer
	int _idx_end;		// Index of the last element (end) in the buffer
	bool isfull;		// Flag indicating whether the buffer is full
	
public:
	CircularBuffer();
	~CircularBuffer();
	CircularBuffer(const CircularBuffer& cb);

	/**
     * Constructor to initialize a buffer with a specific capacity.
     * @param capacity The maximum number of elements the buffer can hold.
     */
	explicit CircularBuffer(int capacity);
	
	/**
     * Constructor to initialize a buffer with a specific capacity, 
     * and fill it with the given element.
     * @param capacity The maximum number of elements the buffer can hold.
     * @param elem The value to initialize all elements in the buffer.
     */
	CircularBuffer(int capacity, const value_type& elem);

	/**
     * Access an element by index without bounds checking.
     * @param i Index of the element to access.
     * @return Reference to the element at the specified index.
     */
	value_type& operator[](int i);
	const value_type& operator[](int i) const;

	/**
     * Access an element by index with bounds checking.
     * @param i Index of the element to access.
     * @return Reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
	value_type& at(int i);
	const value_type& at(int i) const;

	/**
     * Get a reference to the first element in the buffer.
     * @return Reference to the first element.
     * @throws std::underflow_error if the buffer is empty.
     */
	value_type& front(); 
	const value_type& front() const;
	
	/**
     * Get a reference to the last element in the buffer.
     * @return Reference to the last element.
     * @throws std::underflow_error if the buffer is empty.
     */
	const value_type& back() const;
	value_type& back();  
	
	/**
     * Linearize the buffer to make it contiguous in memory.
     * @return Pointer to the linearized buffer.
     */
	value_type* linearize();
	
	/**
     * Check if the buffer is already linearized.
     * @return True if the buffer is linearized, false otherwise.
     */
	bool is_linearized() const;
	
	/**
     * Rotate the buffer so that the new beginning is at the specified index.
     * @param new_begin The index of the new beginning of the buffer.
     * @throws std::out_of_range if the index is invalid.
     */
	void rotate(int new_begin);
	
	/**
     * Get the current number of elements in the buffer.
     * @return Number of elements in the buffer.
     */
	int size() const;

	/**
     * Check if the buffer is empty.
     * @return True if the buffer is empty, false otherwise.
     */
	bool empty() const;
	
	/**
     * Check if the buffer is full.
     * @return True if the buffer is full, false otherwise.
     */
	bool full() const;
	
	
	/**
     * Get the number of remaining slots in the buffer.
     * @return Number of unused slots in the buffer.
     */
	int reserve() const;
	
	/**
     * Get the total capacity of the buffer.
     * @return The maximum number of elements the buffer can hold.
     */
	int capacity() const;

	/**
     * Change the buffer capacity. 
     * The size must not exceed the new capacity.
     * @param new_capacity The new capacity for the buffer.
     * @throws std::invalid_argument if the new capacity is smaller than the current size.
     */
	void set_capacity(int new_capacity);
	
	/**
     * Resize the buffer to hold a specific number of elements.
     * If the new size is larger, new elements are initialized with the specified item.
     * @param new_size The new size of the buffer.
     * @param item The value to initialize new elements if the buffer is expanded.
     */
	void resize(int new_size, const value_type& item = value_type());
	
	/**
     * Assignment operator for copying another buffer into this one.
     * @param cb The source buffer to copy.
     * @return Reference to the updated buffer.
     */
	CircularBuffer& operator=(const CircularBuffer& cb);
	
	/**
     * Swap the contents of this buffer with another buffer.
     * @param cb The buffer to swap with.
     */
	void swap(CircularBuffer& cb);

	/**
     * Add an element to the end of the buffer.
     * If the buffer is full, the first element is overwritten.
     * @param item The element to add to the buffer.
     */
	void push_back(const value_type& item = value_type());
	
	/**
     * Add an element to the front of the buffer.
     * If the buffer is full, the last element is overwritten.
     * @param item The element to add to the front of the buffer.
     */
	void push_front(const value_type& item = value_type());
	
	/**
     * Remove the last element from the buffer.
     * @throws std::out_of_range if the buffer is empty.
     */
	void pop_back();
	
	/**
     * Remove the first element from the buffer.
     * @throws std::out_of_range if the buffer is empty.
     */
	void pop_front();

	/**
     * Insert an element at a specific position in the buffer.
     * @param pos The position where the element will be inserted.
     * @param item The value to insert.
     * @throws std::out_of_range if the position is invalid.
     */
	void insert(int pos, const value_type& item = value_type());
	
	/**
     * Remove a range of elements from the buffer.
     * @param first The start of the range to remove (inclusive).
     * @param last The end of the range to remove (exclusive).
     * @throws std::out_of_range if the range is invalid.
     */
	void erase(int first, int last);
	
	/**
     * Clear the buffer, removing all elements.
     * @throws std::underflow_error if the buffer is already empty.
     */
	void clear();
};

/**
 * Compare two buffers for equality.
 * @param a The first buffer.
 * @param b The second buffer.
 * @return True if the buffers are equal, false otherwise.
 */
bool operator==(const CircularBuffer& a, const CircularBuffer& b);

/**
 * Compare two buffers for inequality.
 * @param a The first buffer.
 * @param b The second buffer.
 * @return True if the buffers are not equal, false otherwise.
 */
bool operator!=(const CircularBuffer& a, const CircularBuffer& b);

