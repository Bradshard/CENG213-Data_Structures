// test_des.cpp
#include <iostream>
#include <string>
#include "DES.h"


int main() {
    int patient_arrival_times[2] = {2,2};
    int urgency_levels[2] = {2,1};

    // Create the DES simulation.
    // Arguments: numTriages, numDoctors, numTiers, triageDuration, doctorVisitDuration, boringDuration, numPatients, patients array.
    DES sim(2, 2, 3, 4, 5, 6, 2,  urgency_levels, patient_arrival_times);
    
    // Run the simulation.
    sim.run();

    return 0;
}
