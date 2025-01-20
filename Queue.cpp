/* 
 * Queue.cpp
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author:  
 * Date:    November 17, 2023
 */

#include "Queue.h"
#include "EmptyDataCollectionException.h"
#include <iostream>

using std::cout;
using std::endl;

// Description: Constructor
template <class ElementType>
Queue<ElementType>::Queue() : 
    elementCount(0), 
    capacity(INITIAL_CAPACITY), 
    frontindex(0), 
    backindex(0), 
    elements(new ElementType[INITIAL_CAPACITY]) {
}

// Description: Destructor
// Postcondition: elements[] is recycled
template <class ElementType>
Queue<ElementType>::~Queue() {
    if (elements) {
        delete[] elements;
        elements = nullptr;
    }
}

// Description: Returns true if this Queue is empty, otherwise false.
// Postcondition: This Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::isEmpty() const {
    return elementCount == 0;
}

// Description:  Change the capacity of the array to newlen
// Precondition:  newlen >= INITIAL_CAPACITY
template <class ElementType>
bool Queue<ElementType>::resize(unsigned newlen) {
    // no size change => nothing to do
    if (newlen == capacity) return true;

    // precondition check
    if (newlen < INITIAL_CAPACITY) return true;

    // allocate new space
    ElementType* newElements = new ElementType[newlen];
    if (newElements == nullptr) return false;

    // copy elements to new space
    for (unsigned int i=0; i<elementCount; i++) {
        newElements[i] = elements[(i+frontindex) % capacity];
    }

    // recycle new space
    delete [] elements;
    elements = newElements;

    // update properties
    capacity = newlen;
    frontindex = 0;
    backindex = (elementCount % capacity);

    return true;
}

// Description: Inserts newElement at the "back" of this Queue 
//              (not necessarily the "back" of this Queue's data structure) 
//              and returns true if successful, otherwise false.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::enqueue(ElementType & newElement) {
    if (elementCount == capacity) {
        // no more space: double the capacity
        if (!resize(capacity * 2)) {
            return false;
        }
    }
    elementCount++;
    elements[backindex] = newElement;
    backindex = (backindex + 1) % capacity;
    return true;
}

// Description: Removes (but does not return) the element at the "front" of this Queue 
//              (not necessarily the "front" of this Queue's data structure).
// Precondition: This Queue is not empty.
// Exception: Throws EmptyDataCollectionException if this Queue is empty.   
// Time Efficiency: O(1)
template <class ElementType>
void Queue<ElementType>::dequeue() {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("dequeue() called but Queue is empty.");
    }
    if (elementCount <= capacity / 4) {
        if (capacity / 2 >= INITIAL_CAPACITY) {
            if (!resize(capacity / 2)) {
                // cout << "resize failed" << endl;
            }
        }
    }
    elementCount--;
    frontindex = (frontindex + 1) % capacity;
}

// Description: Returns (but does not remove) the element at the "front" of this Queue
//              (not necessarily the "front" of this Queue's data structure).
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged by this operation.
// Exception: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType & Queue<ElementType>::peek() const {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("peek() called but Queue is empty.");
    }
    return elements[frontindex];
}

// Description: Prints the elements of the Queue.
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(n), where n is the number of elements in the Queue.
template <class ElementType>
void Queue<ElementType>::print() const {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("print() called with an empty Queue.");
    }
    for (unsigned int i = frontindex; i != backindex; i = (i+1)% capacity) {
        elements[i].print();
        cout << endl;
    }
}