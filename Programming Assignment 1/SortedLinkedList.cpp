#include "SortedLinkedList.h"

SortedLinkedList::SortedLinkedList()
{
    // YOUR CODE GOES HERE
    /* LinkedList deals with this*/
}

SortedLinkedList::~SortedLinkedList()
{
    // YOUR CODE GOES HERE
    /* LinkedList deals with this*/
}

void SortedLinkedList::add(const Event& data)
{
    // YOUR CODE GOES HERE
    if(list.isEmpty()){
        list.addFront(data);
        return;
    }
    
    Node<Event>* curr = list.head;
    while(curr != NULL && !(data < curr->data)){
        curr = curr->next;
    }
    
    if(curr == NULL){
        list.addBack(data);
    }
    else if(curr == list.head){
        list.addFront(data);
    }
    else{
        Node<Event>* bc = new Node<Event>(data);
        bc->next = curr;
        bc->prev = curr->prev;
        curr->prev->next = bc;
        curr->prev = bc;
    }
}

Event SortedLinkedList::removeSmallest()
{
    // YOUR CODE GOES HERE
    return list.removeFront();
}

bool SortedLinkedList::isEmpty() const
{
    // YOUR CODE GOES HERE
    return list.isEmpty();
}
Event SortedLinkedList::getFirst() const
{
    return list.getFront();
}

Event SortedLinkedList::getLast() const
{
    return list.getBack();   
}
