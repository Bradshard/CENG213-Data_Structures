#ifndef TIEREDFCFSQUEUE_H
#define TIEREDFCFSQUEUE_H

#include "FCFSQueue.h"

class TieredFCFSQueue {
private:
    FCFSQueue* tiers;
    int numTiers;

public:
    TieredFCFSQueue(); // you may initialize with one tier in default constructor, you may also remove this function if not needed
    TieredFCFSQueue(int k);
    ~TieredFCFSQueue();
    void enqueue(int patientId, int tier);
    int dequeue();
    int getFirst() const;
    int getLast() const;
    bool isEmpty() const;
    
    friend class DES;
};

#endif
