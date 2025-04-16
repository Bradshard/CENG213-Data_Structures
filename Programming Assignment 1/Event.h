#ifndef EVENT_H
#define EVENT_H

#include <iostream>

enum EventType
{
    TriageQueueEntrance, // a patient enters to triage queue
    TriageEntrance, /* a patient enters to triage (triage queue wait is finished) */
    TriageLeave, // a patient leaves triage
    DoctorQueueEntrance, /* a patient enters into doctor queue */ 
    DoctorEntrance, /* a patient enters to doctor exemination (doctor queue wait is finished) */
    PatientLeaveHospital, /* a patients compelete doctor visit and leaves the hospital */
    TriageQueueBoringStart, /* a patient in triage queue gets bored and leaves the hospital */
    DoctorQueueBoringStart /* a patient in doctor queue gets bored and leaves the hospital */
};

class Event
{
public:
    int time; // -1, if not applicable
    EventType type;
    int patientId;  // -1 if not applicable
    int resourceId; // Triage/Doctor ID, -1 if not applicable
    Event(int t, EventType et, int pid, int rid);
    bool operator<(const Event& other) const;
    
    Event();
    Event(const Event& other); // copy constructor
    Event& operator=(const Event& other); // assignment operator
    
    // Overloading the << operator to enable easy printing of Event objects
    // This allows us to use `std::cout << event;` instead of writing a separate print() function.
    /*
    example output:
    [TIME 11] Event Type: 3,  Patient Id: 2, Resource Id: 0
    */
    friend std::ostream& operator<<(std::ostream& os, const Event& event);
    
};

#endif