/* 
 * BankSimApp.cpp
 *
 * Description: Bank Simulation Application using PriorityQueue and Queue
 * 
 * Author:  
 * Date:    November 17, 2023
 *
 */  

#include <iostream>
#include <iomanip>
#include <string>
#include "EmptyDataCollectionException.h"
#include "Event.h"
#include "Queue.h"
#include "BinaryHeap.h"
#include "PriorityQueue.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stoi;
using std::setw;

void simulate();
void processArrival(Event& anEvent, PriorityQueue<Event>* eventpq, Queue<Event>* bankq, bool& tp);
double processDeparture(Event& anEvent, PriorityQueue<Event>* eventpq, Queue<Event>* bankq, bool& tp);

int main() {
    simulate();
    return 0;
}

// Description: Performs the simulation
void simulate() {
    cout << "Simulation Begins" << endl;
    int peopleprocessed = 0;
    double totalwaittime = 0;
    // bankLine = a new empty queue // Bank line
    Queue<Event>* bankLine = new Queue<Event>();
    // eventPriorityQueue = a new empty priority queue // Event queue
    PriorityQueue<Event>* eventPriorityQueue = new PriorityQueue<Event>();
    // tellerAvailable = true
    bool teller = true;
    int currentTime = 0;

    string line;
    string arrivaltime;
    string transactiontime;
    string delimiter = " ";
    size_t pos = 0;
    unsigned int a;
    unsigned int t;
    //Create and add arrival events to event queue
    // while(datafile is not empty)
    while (getline(cin,line)) 
    {
        // Get next arrival time a and transaction time t from file
        pos = line.find(delimiter);
        arrivaltime = line.substr(0,pos);
        line.erase(0, pos + delimiter.length());
        transactiontime = line;
        a = stoi(arrivaltime);
        t = stoi(transactiontime);
        // newArrivalEvent = a new arrival event containing a and t
        Event newArrivalEvent = Event('A',a,t);
        // eventPriorityQueue.enqueue(newArrivalEvent)
        try {eventPriorityQueue->enqueue(newArrivalEvent);}
        catch (EmptyDataCollectionException& anException) {}
    }

    //Event loop
    // while(eventPriorityQueue is not empty)
    while (!eventPriorityQueue->isEmpty()) {
        // newEvent = eventPriorityQueue.peekFront()
        Event newEvent;
        try {newEvent = eventPriorityQueue->peek();}
        catch (EmptyDataCollectionException& anException) {}
        //Get current time
        // currentTime = time of newEvent
        currentTime = newEvent.getTime();
        double waittime = 0;
        // if (newEvent is an arrival event)
        if (newEvent.isArrival()) {
            processArrival(newEvent,eventPriorityQueue,bankLine,teller);
        } else {
            waittime = processDeparture(newEvent,eventPriorityQueue,bankLine,teller);
            peopleprocessed++;
            totalwaittime += waittime;
        }
    }
    delete bankLine;
    delete eventPriorityQueue;
    cout << "Simulation Ends" << endl << endl;
    cout << "Final Statistics:" << endl << endl;
    cout << "\tTotal number of people processed: " << peopleprocessed << endl;
    double avgwaittime = totalwaittime / peopleprocessed;
    cout << "\tAverage amount of time spent waiting: " << avgwaittime << endl << endl;
}

//Processes an arrival event
// processArrival(arrivalEvent: Event, eventPriorityQueue: PriorityQueue, bankLine: Queue)
void processArrival(Event& arrivalEvent, PriorityQueue<Event>* eventpq, Queue<Event>* bankq, bool& teller) {
    //Remove this event from the event queue
    // eventPriorityQueue.dequeue()
    int currentTime = arrivalEvent.getTime();
    cout << "Processing an arrival event at time:" << setw(6) << currentTime << endl;
    try {eventpq->dequeue();}
    catch (EmptyDataCollectionException& anException) {}
    // customer = customer referenced in arrivalEvent
    Event customer = arrivalEvent;
    // if (bankLine.isEmpty() && tellerAvailable)
    if (bankq->isEmpty() && teller) {
        // departureTime = currentTime + transaction time in arrivalEvent
        int departureTime = currentTime + customer.getLength();
        // newDepartureEvent = a new departure event with departureTime
        Event newDepartureEvent = Event('D',departureTime);
        eventpq->enqueue(newDepartureEvent);
        teller = false;
    } else {
        bankq->enqueue(customer); 
    }
}

//Processes a departure event
// processDeparture(departureEvent: Event, eventPriorityQueue: PriorityQueue, bankLine: Queue)
double processDeparture(Event& departureEvent, PriorityQueue<Event>* eventpq, Queue<Event>* bankq, bool& teller) {
    //Remove this event from the event queue
    int currentTime = departureEvent.getTime();
    cout << "Processing a departure event at time:" << setw(5) << currentTime << endl;
    try {eventpq->dequeue();}
    catch (EmptyDataCollectionException& anException) {}
    int waittime = 0;
    // if (!bankLine.isEmpty())
    if (!bankq->isEmpty()) {
        //Customer at front of line begins transaction
        // customer = bankLine.peekFront()
        Event customer;
        try {customer = bankq->peek();}
        catch (EmptyDataCollectionException& anException) {}
        // bankLine.dequeue()
        try {bankq->dequeue();}
        catch (EmptyDataCollectionException& anException) {}
        
        // departureTIme = currentTime + transaction time in customer
        int departureTime = currentTime + customer.getLength();
        // newDepartureEvent = a new departure event with departureTime
        Event newDepartureEvent = Event('D',departureTime);
        // eventPriorityQueue.enqueue(newDepartureEvent)
        eventpq->enqueue(newDepartureEvent);
        waittime = currentTime - customer.getTime();
    } else {
        teller = true;
    }
    return waittime;
}