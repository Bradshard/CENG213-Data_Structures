#include "FCFSQueue.h"

void FCFSQueue::enqueue(int patientId)
{
    // YOUR CODE GOES HERE
    patients.addBack(patientId);
}

int FCFSQueue::dequeue()
{
    // YOUR CODE GOES HERE
    return patients.removeFront();
}

bool FCFSQueue::isEmpty() const
{
    // YOUR CODE GOES HERE
    return patients.isEmpty();
}

int FCFSQueue::getFirst() const
{
    // YOUR CODE GOES HERE
    return patients.getFront();
}

int FCFSQueue::getLast() const
{
    // YOUR CODE GOES HERE
    return patients.getBack();
}
int FCFSQueue::removeBack()
{
    return patients.removeBack();
}
