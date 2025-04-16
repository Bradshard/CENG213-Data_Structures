#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include "LinkedList.h"
#include "Event.h"

class SortedLinkedList {
private:
    LinkedList<Event> list;

public:
    SortedLinkedList();
    ~SortedLinkedList();
    void add(const Event& data);
    Event removeSmallest();
    bool isEmpty() const;
    Event getFirst() const;
    Event getLast() const;
    friend class PriorityQueue;
};

#endif
