/* 
 * BinaryHeap.cpp
 *
 * Description: Minimum Binary Heap ADT class.
 * Class Invariant: Always a Minimum Binary Heap.
 *
 * Author:  
 * Date:    November 17, 2023
 */

#include <iostream>
#include "BinaryHeap.h"  // Header file

using std::cout;
using std::endl;

// Description: Constructor
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap() : 
    elementCount(0),
    capacity(INITIAL_CAPACITY),
    elements(new ElementType[INITIAL_CAPACITY]) {
}
  
// Description: Destructor
template <class ElementType>
BinaryHeap<ElementType>::~BinaryHeap() {
    if (elements) {
        delete[] elements;
        elements = nullptr;
    }
}

// Description: Returns the number of elements in the Binary Heap.
// Postcondition: The Binary Heap is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
unsigned int BinaryHeap<ElementType>::getElementCount() const {
    return elementCount;
}

// Description:  Change the capacity of the array to newlen
// Precondition:  newlen >= INITIAL_CAPACITY
template <class ElementType>
bool BinaryHeap<ElementType>::resize(unsigned newlen) {
    // no size change => do nothing
    if (newlen == capacity) return true;

    // precondition check
    if (newlen < INITIAL_CAPACITY) return true;

    // allocate new psace
    ElementType* newElements = new ElementType[newlen];
    if (newElements == nullptr) return false;

    // copy elements to new space
    for (unsigned int i=0; i<elementCount; i++) {
        newElements[i] = elements[i];
    }

    // recycle new space
    delete [] elements;
    elements = newElements;

    // update properties
    capacity = newlen;
    return true;
}

// Description: Inserts newElement into the Binary Heap. 
//              It returns true if successful, otherwise false.      
// Time Efficiency: O(log2 n)
template <class ElementType>
bool BinaryHeap<ElementType>::insert(ElementType & newElement) {
    // if Queue is full, double the capacity
    if (elementCount == capacity) {
        if (!resize(capacity * 2)) {
            return false;
        }
    }
    // add newElement to back of queue
    elements[elementCount] = newElement;
    elementCount++;
    // perform reHeapUp
    reHeapUp(elementCount - 1);
    return true;
}

// Utility method
// Description: Recursively put the array back into a Minimum Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned int indexOfBottom) {
    // Base case: root of the heap
    if (indexOfBottom == 0) {
        return;
    }
    // Recursive case: not at the root
    else {
        unsigned int indexOfParent = (indexOfBottom - 1) / 2;
        // if parent > child, swap
        if (!(elements[indexOfParent] <= elements[indexOfBottom])) {
            ElementType temp = elements[indexOfBottom];
            elements[indexOfBottom] = elements[indexOfParent];
            elements[indexOfParent] = temp;
        }
        reHeapUp(indexOfParent);
    }
}


// Description: Removes (but does not return) the necessary element.
// Precondition: This Binary Heap is not empty.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void BinaryHeap<ElementType>::remove() {  

   if(elementCount == 0) 
      throw EmptyDataCollectionException("remove() called with an empty BinaryHeap.");

   elements[0] = elements[elementCount - 1];
   elementCount--;
   
   // No need to call reheapDown() is we have just removed the only element
   if ( elementCount > 0 ) 
      reHeapDown(0);
   
   return;   
}

// Utility method
// Description: Recursively put the array back into a Minimum Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned int indexOfRoot) {

   unsigned int indexOfMinChild = indexOfRoot;
   
   // Find indices of children.
   unsigned int indexOfLeftChild = 2 * indexOfRoot + 1;
   unsigned int indexOfRightChild = 2 * indexOfRoot + 2;

   // Base case: elements[indexOfRoot] is a leaf as it has no children
   if (indexOfLeftChild > elementCount - 1) return;

   // If we need to swap, select the smallest child
   // If (elements[indexOfRoot] > elements[indexOfLeftChild])
   if ( ! (elements[indexOfRoot] <= elements[indexOfLeftChild]) )
      indexOfMinChild = indexOfLeftChild;

   // Check if there is a right child, is it the smallest?
   if (indexOfRightChild < elementCount) {
      // if (elements[indexOfMinChild] > elements[indexOfRightChild])
      if ( ! (elements[indexOfMinChild] <= elements[indexOfRightChild]) )
         indexOfMinChild = indexOfRightChild;
   }

   // Swap parent with smallest of children.
   if (indexOfMinChild != indexOfRoot) {
      
      ElementType temp = elements[indexOfRoot];
      elements[indexOfRoot] = elements[indexOfMinChild];
      elements[indexOfMinChild] = temp;
      
      // Recursively put the array back into a heap
      reHeapDown(indexOfMinChild);
   }
   return;
} 

// Description: Retrieves (but does not remove) the necessary element.
// Precondition: This Binary Heap is not empty.
// Postcondition: This Binary Heap is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(1) 
template <class ElementType>
ElementType & BinaryHeap<ElementType>::retrieve() const {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("retrieve() called with an empty BinaryHeap.");
    }
    return elements[0];
}

// Description: Prints the elements of the Binary Heap in level order.
// Precondition: This Binary Heap is not empty.
// Postcondition: This Binary Heap is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(n), where n is the number of elements in the Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::print() const {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("print() called with an empty BinaryHeap.");
    }
    for (unsigned int i=0; i<elementCount; i++) {
        elements[i].print();
        cout << endl;
    }
}