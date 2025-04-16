#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "SortedLinkedList.h"

class PriorityQueue {
private:
    SortedLinkedList events;

public:
    void enqueue(const Event& e);
    Event dequeue();
    bool isEmpty() const;
    
    Event getFirst() const;
    Event getLast() const;
};

#endif