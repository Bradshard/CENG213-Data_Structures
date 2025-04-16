#include "FCFSQueue.h"
#include <iostream>

int main() {
    // Create a FCFSQueue instance for patient IDs
    FCFSQueue queue;

    // part 1: Check if the queue is initially empty
    std::cout << "part 1: Is the queue empty initially? " << queue.isEmpty() << std::endl;  // Expected: 1 (true)

    // part 2: Enqueue some patients into the queue
    std::cout << "part 2: Enqueue patients 101, 102, and 103" << std::endl;
    queue.enqueue(101);  // Patient 101
    queue.enqueue(102);  // Patient 102
    queue.enqueue(103);  // Patient 103

    // part 3: Check the queue length after enqueuing
    std::cout << "part 3: Is the queue empty? " << queue.isEmpty() << std::endl;  // Expected: 0 (false)
    std::cout << "part 4: Length of the queue (Expected: 3): " << queue.isEmpty() << std::endl;

    // part 4: Dequeue patients and check the order
    std::cout << "part 4: Dequeue patients in order" << std::endl;
    std::cout << "Dequeued patient: " << queue.dequeue() << std::endl;  // Expected: 101
    std::cout << "Dequeued patient: " << queue.dequeue() << std::endl;  // Expected: 102

    // part 5: Check if queue is empty after dequeueing some patients
    std::cout << "part 5: Is the queue empty? " << queue.isEmpty() << std::endl;  // Expected: 0 (false)

    // part 6: Dequeue the last patient
    std::cout << "part 6: Dequeue the last patient" << std::endl;
    std::cout << "Dequeued patient: " << queue.dequeue() << std::endl;  // Expected: 103

    // part 7: Check if the queue is empty after all patients are dequeued
    std::cout << "part 7: Is the queue empty? " << queue.isEmpty() << std::endl;  // Expected: 1 (true)

    return 0;
}
