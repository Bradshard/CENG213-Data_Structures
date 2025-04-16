#include "DES.h"
#include "Event.h"
#include <iostream>
#include <cstdlib>

DES::DES(int numTriages, int numDoctors, int numTiers, int tDuration, int dDuration, int bDuration,
int numPatients, int* urgencyLevels, int* patientArrivalTimes) : doctorQueue(numTiers)
{
    // YOUR CODE GOES HERE
    this->numTriages = numTriages;
    this->numDoctors = numDoctors;
    this->numTiers = numTiers;
    this->triageDuration = tDuration;
    this->doctorVisitDuration = dDuration;
    this->boringDuration = bDuration;
    

    triageAvailable = new bool[numTriages];
    doctorAvailable = new bool[numDoctors];
    doctorStacks = new MonotonicStack[numDoctors];

    for (int i = 0; i < numTriages; i++) {
        triageAvailable[i] = true;
    }

    for (int i = 0; i < numDoctors; i++) {
        doctorAvailable[i] = true;
    }

    this->urgencyLevels = new int[numPatients];
    for (int i = 0; i < numPatients; i++) {
        this->urgencyLevels[i] = urgencyLevels[i];

        Event e(patientArrivalTimes[i], TriageQueueEntrance, i, -1);
        // e is given in processEvent, so use it.
        eventQueue.enqueue(e);
    }
    
}

DES::~DES()
{
    // YOUR CODE GOES HERE
    delete[] triageAvailable;
    delete[] doctorAvailable;
    delete[] doctorStacks;
    delete[] urgencyLevels;
}

void DES::run()
{
    // YOUR CODE GOES HERE
    while(!(eventQueue.isEmpty())){
        Event e = eventQueue.dequeue();
        int res_id= e.resourceId;
        if (e.type == PatientLeaveHospital) {
            res_id = -1;
        }
        std::cout << "[TIME " << e.time << "] Event Type: " << e.type << ", Patient Id: " << e.patientId<< ", Resource Id: " <<res_id << std::endl;
        processEvent(e); // e is given in processEvent, so use it.
    }
    std::cout << "Simulation finished." << std::endl;
    
    for(int i = 0; i < numDoctors; i++){
        std::cout << "Monotonic Stack of Doctor " << i << " is " << doctorStacks[i] << std::endl;
    }
}

void DES::processEvent(const Event& e)
{
    // YOUR CODE GOES HERE
    if (e.type == TriageQueueEntrance)
    {
        triageQueue.enqueue(e.patientId);

        // we check boredom.
        eventQueue.enqueue(Event(e.time + boringDuration, TriageQueueBoringStart, e.patientId, -1));

        // passing to available triages.
        for (int i = 0; i < numTriages; i++) {
            if (triageAvailable[i] && !(triageQueue.isEmpty())) {
                triageAvailable[i] = false;
                triageQueue.dequeue();

                // triage entrance scheduling.
                eventQueue.enqueue(Event(e.time, TriageEntrance, e.patientId, i));
                break;
            }
        }
    }
    else if (e.type == TriageEntrance)
    {
        // Right after we enter triage.
        eventQueue.enqueue(Event(e.time + triageDuration, TriageLeave, e.patientId, e.resourceId));
    }
    // now leave triage
    else if (e.type == TriageLeave)
    {
        triageAvailable[e.resourceId] = true;

        // then we will go to doctors, after scheduled.
        eventQueue.enqueue(Event(e.time, DoctorQueueEntrance, e.patientId, -1));

        // next triage
        for (int i = 0; i < numTriages; i++) {
            if (triageAvailable[i] && !(triageQueue.isEmpty())) {
                int pid = triageQueue.getFirst();
                triageQueue.dequeue();
                triageAvailable[i] = false;

                eventQueue.enqueue(Event(e.time, TriageEntrance, pid, i));
                break;
            }
        }
    }
    else if (e.type == DoctorQueueEntrance)
    {
        int tier = urgencyLevels[e.patientId];
        doctorQueue.enqueue(e.patientId, tier);

        // we stated that person can get bored at doctors too
        eventQueue.enqueue(Event(e.time + boringDuration, DoctorQueueBoringStart, e.patientId, -1));

        // then lets go to doctors office, if available
        for (int i = 0; i < numDoctors; i++) {
            if (doctorAvailable[i] && !doctorQueue.isEmpty()) {
                int pid = doctorQueue.getFirst();
                doctorQueue.dequeue();
                doctorAvailable[i] = false;

                eventQueue.enqueue(Event(e.time, DoctorEntrance, pid, i));
                break;
            }
        }
    }
    else if (e.type == DoctorEntrance)
    {
        // doctor appointment time.
        eventQueue.enqueue(Event(e.time + doctorVisitDuration, PatientLeaveHospital, e.patientId, e.resourceId));
    }
    else if (e.type == PatientLeaveHospital)
    {
        int did = e.resourceId;
        int pid = e.patientId;
        if(did != -1){
            doctorAvailable[did] = true;
            doctorStacks[did].push(pid);
            
            if (!(doctorQueue.isEmpty())) {
                int nextPid = doctorQueue.getFirst();
                doctorQueue.dequeue();
                
                doctorAvailable[did] = false;
                eventQueue.enqueue(Event(e.time, DoctorEntrance, nextPid, did));
            }
        }
    }
    else if (e.type == TriageQueueBoringStart)
    {
        int pid = e.patientId;

        if (!(triageQueue.isEmpty()) && triageQueue.getLast() == pid) {
            // Patient leaves the hospital due to boredom
            triageQueue.removeBack(); //removing the person.
            eventQueue.enqueue(Event(e.time, PatientLeaveHospital, pid, -1));
        }
    }
    else if (e.type == DoctorQueueBoringStart)
    {
        int pid = e.patientId;

        for (int i = numTiers - 1; i >= 0; i--) {
            if (!(doctorQueue.tiers[i].isEmpty()) && doctorQueue.tiers[i].getLast() == pid) {
                doctorQueue.tiers[i].removeBack(); // remove by the help of friend functionality.
                eventQueue.enqueue(Event(e.time, PatientLeaveHospital, pid, -1));
                break;
            }
        }
    }
}
