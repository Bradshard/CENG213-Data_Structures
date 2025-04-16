#include "Event.h"

Event::Event(int t, EventType et, int pid, int rid)
{
    // YOUR CODE GOES HERE
    time = t;
    type = et;
    patientId = pid;
    resourceId = rid;
    /* not constant values, so;
     we don't need to use
     Event::Event(int t, EventType et, int pid, int rid) : time(t),type(et),patientId(pid), resourceId(rid) {} type of constructor.*/
}

bool Event::operator<(const Event& other) const
{
    // YOUR CODE GOES HERE
    if(this->time != other.time){
        return this->time < other.time ;
    }
    if(this->patientId != other.patientId){
        return this->patientId < other.patientId ;
    }
    if(this->type != other.type){
        return this->type < other.type ;
    }

    return this->resourceId < other.resourceId;
}

Event::Event()
{
    // YOUR CODE GOES HERE
    time = -1;
    type = TriageQueueEntrance;
    patientId = -1;
    resourceId = -1;
}

Event::Event(const Event& other)
{
    // YOUR CODE GOES HERE
    this->time = other.time;
    this->type = other.type;
    this->patientId = other.patientId;
    this->resourceId = other.resourceId;
}

// Assignment operator
Event& Event::operator=(const Event& other)
{
    // YOUR CODE GOES HERE
    if(this != &other){
        this->time = other.time;
        this->type = other.type;
        this->patientId = other.patientId;
        this->resourceId = other.resourceId;
    }
    return *this;
}


// Overloaded << operator: This function allows us to print Event objects using std::cout.
// Instead of writing event.print(), we can directly use `std::cout << event;`
/*
example output:
[TIME 11] Event Type: 3,  Patient Id: 2, Resource Id: 0
*/
std::ostream& operator<<(std::ostream& os, const Event& event)
{
    // YOUR CODE GOES HERE
    
    os << "[TIME " << event.time << "] Event Type: " << event.type << ", Patient Id: " << event.patientId<< ", Resource Id: " << event.resourceId;;
    return os;
}
