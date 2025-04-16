#include "Event.h"
#include <iostream>

using namespace std;

int main() {
    // part 1: Basic Event creation and print
    Event event1(10, DoctorEntrance, 5, 1);
    cout<<event1<<endl;

    // part 2: Copy constructor
    Event event2 = event1;
    cout<<event2<<endl;

    // part 3: Assignment operator
    Event event3(20, TriageQueueEntrance, 10, -1);
    event3 = event1;
    cout<<event3<<endl;

    // part 4: Comparison operator (time comparison)
    Event event4(15, PatientLeaveHospital, 3, 2);
    Event event5(16, PatientLeaveHospital, 3, 2);
    std::cout << "event4 < event5 (time): " << (event4 < event5) << std::endl; // 1
    std::cout << "event5 < event4 (time): " << (event5 < event4) << std::endl; // 0

    // part 5: Comparison operator (patientId comparison)
    Event event6(15, PatientLeaveHospital, 4, 2);
    std::cout << "event4 < event6 (patientId): " << (event4 < event6) << std::endl; // 1
    std::cout << "event6 < event4 (patientId): " << (event6 < event4) << std::endl; // 0

    // part 6: Comparison operator (resourceId comparison)
    Event event7(15, PatientLeaveHospital, 3, 3);
    std::cout << "event4 < event7 (resourceId): " << (event4 < event7) << std::endl; // 1
    std::cout << "event7 < event4 (resourceId): " << (event7 < event4) << std::endl; // 0

    // part 7: Comparison operator (eventType comparison, when all other fields are equal)
    Event event8(15, DoctorQueueEntrance, 3, 2);
    std::cout << "event4 < event8 (eventType): " << (event4 < event8) << std::endl; // 0
    std::cout << "event8 < event4 (eventType): " << (event8 < event4) << std::endl; // 1

    // part 8: Copy and modify
    Event event12 = event1;
    event12.time = 100;
    cout<<event12<<endl;
    cout<<event1<<endl; //Ensure event1 is unchanged

    // part 9: Self assignment
    event1 = event1;
    cout<<event1<<endl;

    return 0;
}

// Expected output:
// [TIME 10] Event Type: 4, Patient Id: 5, Resource Id: 1
// [TIME 10] Event Type: 4, Patient Id: 5, Resource Id: 1
// [TIME 10] Event Type: 4, Patient Id: 5, Resource Id: 1
// event4 < event5 (time): 1
// event5 < event4 (time): 0
// event4 < event6 (patientId): 1
// event6 < event4 (patientId): 0
// event4 < event7 (resourceId): 1
// event7 < event4 (resourceId): 0
// event4 < event8 (eventType): 0
// event8 < event4 (eventType): 1
// [TIME 5] Event Type: 7, Patient Id: -1, Resource Id: -1
// [TIME 25] Event Type: 9, Patient Id: -1, Resource Id: 4
// [TIME 30] Event Type: 10, Patient Id: -1, Resource Id: 2
// [TIME 100] Event Type: 5, Patient Id: 5, Resource Id: 1
// [TIME 10] Event Type: 5, Patient Id: 5, Resource Id: 1
// [TIME 10] Event Type: 5, Patient Id: 5, Resource Id: 1