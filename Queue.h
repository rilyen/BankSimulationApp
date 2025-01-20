/* 
 * Queue.h 
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author:  
 * Date:    November 17, 2023
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "EmptyDataCollectionException.h"
#include "Event.h"

template <class ElementType>
class Queue {
    private:
        static unsigned const INITIAL_CAPACITY = 6;
        ElementType* elements;
        unsigned elementCount;
        unsigned capacity;
        unsigned frontindex;
        unsigned backindex;

        bool resize (unsigned len);
    public:
        /******* Start of Queue Public Interface *******/
        // Class Invariant:  FIFO or LILO order

        // Description: Constructor
        Queue();

        // Description: Destructor
        ~Queue();

        // Description: Returns true if this Queue is empty, otherwise false.
        // Postcondition: This Queue is unchanged by this operation.
        // Time Efficiency: O(1)
        bool isEmpty() const;
        
        // Description: Inserts newElement at the "back" of this Queue 
        //              (not necessarily the "back" of this Queue's data structure) 
        //              and returns true if successful, otherwise false.
        // Time Efficiency: O(1)
        bool enqueue(ElementType & newElement);
        
        // Description: Removes (but does not return) the element at the "front" of this Queue 
        //              (not necessarily the "front" of this Queue's data structure).
        // Precondition: This Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
        // Time Efficiency: O(1)
        void dequeue(); 

        // Description: Returns (but does not remove) the element at the "front" of this Queue
        //              (not necessarily the "front" of this Queue's data structure).
        // Precondition: This Queue is not empty.
        // Postcondition: This Queue is unchanged by this operation.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(1)
        ElementType & peek() const;  

        // Description: Prints the elements of the Queue.
        // Precondition: This Queue is not empty.
        // Postcondition: This Queue is unchanged.
        // Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(n), where n is the number of elements in the Queue.
        void print() const;

        /******* End of Queue Public Interface *******/
};
#include "Queue.cpp"
#endif