#include "MonotonicStack.h"

MonotonicStack::MonotonicStack()
{
    // YOUR CODE GOES HERE
    /* handled by linkedlist*/
}
MonotonicStack::~MonotonicStack()
{
    // YOUR CODE GOES HERE
    /* handled by linkedlist*/
}

void MonotonicStack::push(int patientId)
{
    // YOUR CODE GOES HERE
    while(!(data.isEmpty()) && patientId < data.getBack()){
        data.removeBack();
    }
    data.addBack(patientId);
}

int MonotonicStack::pop()
{
    // YOUR CODE GOES HERE
    return data.removeBack();
}

int MonotonicStack::top() const
{
    // YOUR CODE GOES HERE
    return data.getBack();
}

bool MonotonicStack::isEmpty() const
{
    // YOUR CODE GOES HERE
    return data.isEmpty();
}


std::ostream& operator<<(std::ostream& os, const MonotonicStack& ms)
{
    // YOUR CODE GOES HERE
    Node<int>*curr = ms.data.tail;
    os <<"{";
    while(curr != NULL){
        os<<curr->data;
        if(curr->prev != NULL){
            os <<", ";
            
        }
        curr = curr->prev;
    }
    os << "}";
    return os;
}
