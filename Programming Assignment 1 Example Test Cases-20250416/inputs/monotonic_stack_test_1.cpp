#include "MonotonicStack.h"
#include <iostream>

int main() {
    MonotonicStack ms;

    // Test Case 1: Empty Stack
    std::cout << "Is stack empty? " << ms.isEmpty() << std::endl;

    // Test Case 2: Push elements
    ms.push(5);
    ms.push(10);
    ms.push(7);
    ms.push(15);
    ms.push(6);

    std::cout << "Stack: " << ms << std::endl;
    std::cout << "Is stack empty? " << ms.isEmpty() << std::endl;

    // Test Case 3: Pop elements
    std::cout << "Pop: " << ms.pop() << std::endl;
    std::cout << "Stack: " << ms << std::endl;
    std::cout << "Pop: " << ms.pop() << std::endl;
    std::cout << "Stack: " << ms << std::endl;

    std::cout << "Is stack empty? " << ms.isEmpty() << std::endl;

    // Test Case 4: Push and pop more elements
    ms.push(20);
    ms.push(8);
    ms.push(25);
    ms.push(4);
    std::cout << "Stack: " << ms << std::endl;

    std::cout << "Pop: " << ms.pop() << std::endl;

    std::cout << "Is stack empty? " << ms.isEmpty() << std::endl;

    return 0;
}
