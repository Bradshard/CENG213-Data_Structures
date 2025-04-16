#ifndef FCFSQUEUE_H
#define FCFSQUEUE_H

#include "LinkedList.h"

class FCFSQueue {
private:
    LinkedList<int> patients; // stores patient IDs

public:
    void enqueue(int patientId);
    int dequeue();
    bool isEmpty() const;
    int getFirst() const;
    int getLast() const;
    int removeBack();
};

#endif
