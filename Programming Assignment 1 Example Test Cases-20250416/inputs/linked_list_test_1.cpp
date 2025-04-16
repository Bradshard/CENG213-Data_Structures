#include "LinkedList.h"
#include "Event.h"
#include <iostream>

int main() {
    LinkedList<Event> list;

    // part 1: Empty list
    std::cout << "Is list empty? " << list.isEmpty() << std::endl;
    std::cout << "List length: " << list.length() << std::endl;

    // part 2: Add to front and back
    Event event1(10, DoctorEntrance, 5, 1);
    Event event2(20, TriageQueueEntrance, 10, -1);
    Event event3(30, PatientLeaveHospital, 3, 2);

    list.addFront(event1);
    list.addBack(event2);
    list.addFront(event3);

    std::cout << "Is list empty? " << list.isEmpty() << std::endl;
    std::cout << "List length: " << list.length() << std::endl;

    // part 3: Remove from front and back
    std::cout << "Remove front: " << list.removeFront() << std::endl;
    std::cout << "List length: " << list.length() << std::endl;
    std::cout << "Remove back: " << list.removeBack() << std::endl;
    std::cout << "List length: " << list.length() << std::endl;

    // part 4: Remove remaining element
    std::cout << "Remove front: " << list.removeFront() << std::endl;
    std::cout << "Is list empty? " << list.isEmpty() << std::endl;
    std::cout << "List length: " << list.length() << std::endl;

    // part 5: Add multiple elements and check length
    Event event4(40, TriageLeave, -1, 2);
    Event event5(50, TriageLeave, -1, 4);
    Event event6(60, TriageLeave, 12, 0);

    list.addBack(event4);
    list.addBack(event5);
    list.addBack(event6);

    std::cout << "List length: " << list.length() << std::endl;

    return 0;
}
