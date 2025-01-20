/* 
 * BinaryHeap.h 
 *
 * Description: Minimum Binary Heap ADT class.
 * Class Invariant: Always a Minimum Binary Heap.
 *
 * Author:  
 * Date:    November 17, 2023
 */

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include "EmptyDataCollectionException.h"
#include "Event.h"

template <class ElementType>
class BinaryHeap {
    private:
        static unsigned int const INITIAL_CAPACITY = 6;
        ElementType* elements;
        unsigned elementCount;
        unsigned capacity;
        
        // Utility functions
        void reHeapUp(unsigned int indexOfRoot);
        void reHeapDown(unsigned int indexOfRoot);
        bool resize (unsigned len);
    public:
        /******* Start of Binary Heap  Public Interface *******/
        // Class Invariant: Always a Minimum Binary Heap.	

        // Description: Constructor
        BinaryHeap();

        // Description: Destructor
        ~BinaryHeap();

        // Description: Returns the number of elements in the Binary Heap.
        // Postcondition: The Binary Heap is unchanged by this operation.
        // Time Efficiency: O(1)
        unsigned int getElementCount() const;

        // Description: Inserts newElement into the Binary Heap. 
        //              It returns true if successful, otherwise false.      
        // Time Efficiency: O(log2 n)
        bool insert(ElementType & newElement);
            
        // Description: Removes (but does not return) the necessary element.
        // Precondition: This Binary Heap is not empty.
        // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
        // Time Efficiency: O(log2 n)
        void remove();

        // Description: Retrieves (but does not remove) the necessary element.
        // Precondition: This Binary Heap is not empty.
        // Postcondition: This Binary Heap is unchanged.
        // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
        // Time Efficiency: O(1) 
        ElementType & retrieve() const;

        // Description: Prints the elements of the Binary Heap in level order.
        // Precondition: This Binary Heap is not empty.
        // Postcondition: This Binary Heap is unchanged.
        // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
        // Time Efficiency: O(n), where n is the number of elements in the Binary Heap.
        void print() const;
        /******* End of Binary Heap Public Interface *******/

};
#include "BinaryHeap.cpp"
#endif
