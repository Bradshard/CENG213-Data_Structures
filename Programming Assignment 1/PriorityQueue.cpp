#include "PriorityQueue.h"

void PriorityQueue::enqueue(const Event& e)
{
    // YOUR CODE GOES HERE
    events.add(e);
}

Event PriorityQueue::dequeue()
{
    // YOUR CODE GOES HERE
    return events.removeSmallest();
}

bool PriorityQueue::isEmpty() const
{
    // YOUR CODE GOES HERE
    return events.isEmpty();
}

Event PriorityQueue::getFirst() const
{
    // YOUR CODE GOES HERE
    return events.list.getFront();
}

Event PriorityQueue::getLast() const
{
    // YOUR CODE GOES HERE
    return events.list.getBack();
}
