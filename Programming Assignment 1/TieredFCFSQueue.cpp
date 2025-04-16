#include "TieredFCFSQueue.h"

TieredFCFSQueue::TieredFCFSQueue()  // you may initialize with one tier in default constructor, you may also remove this function if not needed
{
    // YOUR CODE GOES HERE
    numTiers = 1;
    tiers = new FCFSQueue[1];
}

TieredFCFSQueue::TieredFCFSQueue(int k)
{
    // YOUR CODE GOES HERE
    numTiers = k;
    tiers = new FCFSQueue[k];
}

TieredFCFSQueue::~TieredFCFSQueue()
{
    // YOUR CODE GOES HERE
    if (tiers != NULL) {
        delete[] tiers;
        tiers = NULL;
        numTiers = 0;
    }
}

void TieredFCFSQueue::enqueue(int patientId, int tier)
{
    // YOUR CODE GOES HERE
    if(tier >= 0 && tier<numTiers) {
        tiers[tier].enqueue(patientId);
    }
}

int TieredFCFSQueue::dequeue()
{
    // YOUR CODE GOES HERE
    for(int i = 0; i < numTiers; i++){
        if(!(tiers[i].isEmpty())){
            return tiers[i].dequeue();
        }
    }
    return -1;
}

bool TieredFCFSQueue::isEmpty() const
{
    // YOUR CODE GOES HERE
    for(int i = 0; i< numTiers; i++){
        if(!(tiers[i].isEmpty())){
            return false;
        }
    }
    return true;
}



int TieredFCFSQueue::getFirst() const
{
    // YOUR CODE GOES HERE
    for(int i = 0; i< numTiers; i++){
        if(!(tiers[i].isEmpty())){
            return tiers[i].getFirst();
        }
    }
    return -1;
}

int TieredFCFSQueue::getLast() const
{
    // YOUR CODE GOES HERE
    for(int i = numTiers - 1; i>= 0; i--){
        if(!(tiers[i].isEmpty())){
            return tiers[i].getLast();
        }
    }
    return -1;
}
