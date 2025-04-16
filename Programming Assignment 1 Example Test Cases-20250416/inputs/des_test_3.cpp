#include <iostream>
#include "DES.h"

int main() {
    int arrival_times[5] = {1, 2, 4, 6, 8};
    int urgency_levels[5] = {1, 2, 0, 1, 2};

    // DES(numTriages, numDoctors, numTiers, triageDuration, doctorVisitDuration, boringDuration, numPatients, urgencyLevels, arrivalTimes)
    DES sim(2, 2, 3, 3, 4, 5, 5, urgency_levels, arrival_times);

    sim.run();
    return 0;
}
