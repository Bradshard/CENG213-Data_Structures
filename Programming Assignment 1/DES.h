#ifndef DES_H
#define DES_H

#include "PriorityQueue.h"
#include "TieredFCFSQueue.h"
#include "FCFSQueue.h"
#include "MonotonicStack.h"

using namespace std;

class DES
{
private:
    int numTriages, numDoctors, numTiers;
    int triageDuration, doctorVisitDuration, boringDuration;
    FCFSQueue triageQueue;
    TieredFCFSQueue doctorQueue;
    PriorityQueue eventQueue;
    bool* triageAvailable;
    bool* doctorAvailable;
    MonotonicStack* doctorStacks;
    int *urgencyLevels;
    

public:
    DES(int numTriages, int numDoctors, int numTiers, int tDuration, int dDuration, int bDuration,
    int numPatients, int* urgencyLevels, int *patientArrivalTimes);
    ~DES();
    void run();
    void processEvent(const Event& e);
};

#endif