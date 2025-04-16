#ifndef MONOTONICSTACK_H
#define MONOTONICSTACK_H

#include "LinkedList.h"

class MonotonicStack {
private:
    LinkedList<int> data; // stores patient IDs

public:
    MonotonicStack();
    ~MonotonicStack();
    void push(int patientId);
    int pop();
    int top() const;
    bool isEmpty() const;
    
    // Overloading the << operator to enable easy printing of MonotonicStack objects
    // This allows us to use `std::cout << s;` instead of writing a separate print() function.
    /*
    Example Output:
    {7, 5, 3, 1}
    */
    friend std::ostream& operator<<(std::ostream& os, const MonotonicStack& event);
};

#endif