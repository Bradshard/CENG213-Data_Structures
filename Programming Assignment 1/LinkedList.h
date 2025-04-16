#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class MonotonicStack;
class SortedLinkedList;

// Template Node class
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    Node(const T& d) : data(d), next(0), prev(0) {}
};

// Template LinkedList class
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(0), tail(0) {}
    ~LinkedList();
    void addFront(const T& data);
    void addBack(const T& data);
    T removeFront();
    T removeBack();
    bool isEmpty() const;
    int length() const;
    T getFront() const;
    T getBack() const;
    
    friend class SortedLinkedList;
    friend class MonotonicStack;
    friend class FCFSQueue;
    friend class TieredFCFSQueue;
    friend class priorityQueue;
    
    // Overloading the << operator to enable easy printing of MonotonicStack objects
    // This allows us to use `std::cout << s;` instead of writing a separate print() function.
    friend std::ostream& operator<<(std::ostream& os, const MonotonicStack& event);
};

// Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    // YOUR CODE GOES HERE
    while(!(isEmpty())){
        removeFront();
    }
}

// Add element to front
template <typename T>
void LinkedList<T>::addFront(const T& data)
{
    // YOUR CODE GOES HERE
    Node<T>* bc = new Node<T>(data);
    bc->next =head;
    
    if(head !=  NULL){
        head->prev =bc;
    }
    head = bc;
    if(tail == NULL){
        tail =bc;
    }
}

// Add element to back
template <typename T>
void LinkedList<T>::addBack(const T& data)
{
    // YOUR CODE GOES HERE
    // nearly same as above.
    Node<T>* bc = new Node<T>(data);
    bc->prev =tail;
    
    if(tail != NULL){
        tail->next =bc;
    }
    tail = bc;
    if(head == NULL){
        head =bc;
    }
}

// Remove element from front
template <typename T>
T LinkedList<T>::removeFront()
{
    // YOUR CODE GOES HERE
    if(isEmpty()){
        return T();
    }
    
    Node<T>*tmp = head;
    T data = tmp->data;
    head = head->next;

    if(head != NULL){
        head->prev = NULL;
    }
    else{
        tail = NULL;
    }
    delete tmp;
    return data;
}

// Remove element from back
template <typename T>
T LinkedList<T>::removeBack()
{
    // YOUR CODE GOES HERE
    if(isEmpty()){
        return T();
    }
    
    
    Node<T>*tmp = tail;
    T data = tmp->data;
    tail = tail->prev;

    if(tail != NULL){
        tail->next = NULL;
    }
    else{
        head = NULL;
    }
    delete tmp;
    return data;
}

// Check if list is empty
template <typename T>
bool LinkedList<T>::isEmpty() const
{
    // YOUR CODE GOES HERE
    return (head == NULL);
}

// Get length of list
template <typename T>
int LinkedList<T>::length() const
{
    // YOUR CODE GOES HERE
    int i = 0;
    Node<T>*curr =head;
    while(curr != NULL){
        i++;
        curr = curr->next;
    }
    return i;
}

template <typename T>
T LinkedList<T>::getFront() const
{
    // YOUR CODE GOES HERE
    if(!(isEmpty())){
        return head->data;
    }
    return T();
}

template <typename T>
T LinkedList<T>::getBack() const
{
    // YOUR CODE GOES HERE
    if(!(isEmpty())){
        return tail->data;
    }
    return T();
}

#endif
