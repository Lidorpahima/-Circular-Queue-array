#pragma once
#include <exception>
#include "std_lib_facilities.h"
/**
 * Exception thrown when attempting to add to a full ring.
 */
struct ring_overflow : std::exception {};
/**
 * Exception thrown when attempting to remove to a empty ring.
 */
struct ring_underflow : std::exception {};
/**
 * Forward declaration of the ring class template.
 * ring_it class template to recognize the ring class template
 * @tparam T The type of elements stored in the ring buffer.
 * @tparam N The maximum number of elements in the ring buffer.
 */
template<class T, int N>
class ring;
/**
 * Iterator for a ring.
 * 
 * @tparam T Type of elements in the ring.
 * @tparam N Maximum capacity of the ring.
 */
template<class T, int N>
   class ring_it {
    
    const ring<T, N>& r; // Reference to the ring
    int index;
 public:
    /**
     * Constructs an ring_it.
     * 
     * @param r Reference to the ring.
     * @param start Starting position.
     */
        ring_it(const ring<T, N>& r, int start) : r(r), index(start) {}
     /**
     * Operator != (check other index).
     * 
     * @param other Another iterator.
     * @return True if other index different.
     */
        bool operator!=(const ring_it& other) const {
            return index != other.index;
        }
     /**
     * Operator ++ (index +1).
     * 
     * @return Reference to this iterator.
     */
        ring_it& operator++() {
            index = (index + 1) % N;
            return *this;
        }
     /**
     * Operator * get the element at the current position.
     * 
     * @return Element at the current position.
     */
        T operator*() const {
            return r.elements[(r.front + index) % N];
        }
     };
 /**
 *  circular buffer.
 * 
 * @tparam T Element type.
 * @tparam N Buffer capacity.
 */
template<class T, int N>
    class ring {
     friend class ring_it<T, N>; // Grants ring_it access to private members.
        T elements[N];  // Storage for elements.
        int front = 0;  // Front index.
        int rear = -1;  // Rear index.
        int count = 0;  // Number of elements stored.
    
public:
     /**
     * Adds an element to the back.
     * 
     * @param value The element to add.
     */
    void push_back(T value) {
        if (count >= N) throw ring_overflow();
        rear = (rear + 1) % N;
        elements[rear] = value;
        ++count;
    }
    int getCount(){
        return count;
    }
     /**
     * Removes and returns the front element.
     * 
     * @return The front element.
     */
    T pop_front() {
        if (count <= 0) throw ring_underflow();
        T value = elements[front];
        front = (front + 1) % N;
        --count;
        return value;
    }
     /**
     * Outputs the contents of the ring(os).
     * 
     * @param os Output stream.
     * @param r The ring to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ring& r) {
        for (int i = 0; i < r.count; ++i) {
            os << r.elements[(r.front + i) % N] << " ";
        }
        return os;
    }
    
     /**
     * Returns an iterator to the beginning.
     * 
     * @return Iterator to the start.
     */
 ring_it<T, N> begin() const {
        return ring_it<T, N>(*this, 0);
    }
    /**
     * Returns an iterator to the end.
     * 
     * @return Iterator to one past the last element.
     */
    ring_it<T, N> end() const {
        return ring_it<T, N>(*this, count);
    }
};
