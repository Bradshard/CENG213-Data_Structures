#include "SortedLinkedList.h"
#include <iostream>

int main() {
    SortedLinkedList sortedList;

    // part 1: Empty list
    std::cout << "Is list empty? " << sortedList.isEmpty() << std::endl;

    // part 2: Add elements in different orders
    Event event1(10, DoctorEntrance, 5, 1);
    Event event2(20, TriageQueueEntrance, 10, -1);
    Event event3(5, PatientLeaveHospital, 3, 2);
    Event event4(15, TriageLeave, 8, 3);

    sortedList.add(event2);
    sortedList.add(event1);
    sortedList.add(event4);
    sortedList.add(event3);

    std::cout << "Is list empty? " << sortedList.isEmpty() << std::endl;

    // part 3: Remove smallest elements
    Event removed1 = sortedList.removeSmallest();
    std::cout << removed1 << std::endl;

    Event removed2 = sortedList.removeSmallest();
    std::cout << removed2 << std::endl;

    Event removed3 = sortedList.removeSmallest();
    std::cout << removed3 << std::endl;

    Event removed4 = sortedList.removeSmallest();
    std::cout << removed4 << std::endl;

    return 0;
}
