/* 
 * PriorityQueue.cpp
 *
 * Description: Priority Queue implemented with Minimum Binary Heap
 *
 * Class Invariant:  Always a Minimum Binary Heap.
 * 
 * Author:  
 * Date:    November 17, 2023
 *
 */  

#include <iostream>
#include "PriorityQueue.h"

// Description: Constructor
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue() : 
    binaryheap(new BinaryHeap<ElementType>()) {
}

// Description: Destructor
template <class ElementType>
PriorityQueue<ElementType>::~PriorityQueue() {
    if (binaryheap) {
        delete binaryheap;
        binaryheap = nullptr;
    }
}

// Description: Returns true if this Priority Queue is empty, otherwise false.
// Postcondition: This Priority Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
    return binaryheap->getElementCount() == 0;
}

// Description: Inserts newElement in this Priority Queue and 
//              returns true if successful, otherwise false.
// Time Efficiency: O(log2 n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType & newElement) {
    return binaryheap->insert(newElement);
}

// Description: Removes (but does not return) the element with the next
//              "highest" priority value from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void PriorityQueue<ElementType>::dequeue() {
    binaryheap->remove();
}

// Description: Returns (but does not remove) the element with the next 
//              "highest" priority from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged by this operation.
// Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType & PriorityQueue<ElementType>::peek() const {
    return binaryheap->retrieve();
}