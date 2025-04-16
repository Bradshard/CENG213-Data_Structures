#include "PriorityQueue.h"
#include <iostream>

int main() {
    PriorityQueue pq;

    // Test Case 1: Empty Queue
    std::cout << "Is queue empty? " << pq.isEmpty() << std::endl;

    // Test Case 2: Enqueue events
    Event event1(10, DoctorEntrance, 5, 1);
    Event event2(20, TriageQueueEntrance, 10, -1);
    Event event3(5, PatientLeaveHospital, 3, 2);
    Event event4(15, TriageLeave, 12, 3);

    pq.enqueue(event2);
    pq.enqueue(event1);
    pq.enqueue(event4);
    pq.enqueue(event3);

    std::cout << "Is queue empty? " << pq.isEmpty() << std::endl;

    // Test Case 3: Dequeue events (in priority order)
    Event dequeued1 = pq.dequeue();
    std::cout << dequeued1 << std::endl;
    Event dequeued2 = pq.dequeue();
    std::cout << dequeued2 << std::endl;

    Event dequeued3 = pq.dequeue();
    std::cout << dequeued3 << std::endl;

    Event dequeued4 = pq.dequeue();
    std::cout << dequeued4 << std::endl;

    return 0;
}
