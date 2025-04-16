#include "TieredFCFSQueue.h"
#include <iostream>

int main() {

    // part 1: Enqueue and Dequeue (Single Tier)
    TieredFCFSQueue queue1(3);
    queue1.enqueue(10, 0);
    queue1.enqueue(20, 0);
    std::cout << "Dequeue from queue1: " << queue1.dequeue() << std::endl;
    std::cout << "Dequeue from queue1: " << queue1.dequeue() << std::endl;
    std::cout << "Dequeue from queue1: " << queue1.dequeue() << std::endl;

    // part 2: Enqueue and Dequeue (Multiple Tiers)
    TieredFCFSQueue queue2(3);
    queue2.enqueue(100, 2);
    queue2.enqueue(10, 0);
    queue2.enqueue(20, 1);
    queue2.enqueue(30, 2);
    queue2.enqueue(40, 1);
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;
    std::cout << "Dequeue from queue2: " << queue2.dequeue() << std::endl;

    return 0;
}
