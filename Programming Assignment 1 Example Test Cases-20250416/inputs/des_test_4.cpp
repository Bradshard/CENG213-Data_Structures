#include <iostream>
#include "DES.h"

int main() {
    int patient_arrival_times[2] = {1, 2};
    int urgency_levels[2] = {1, 2};

    // DES: No triage (numTriages = 0), 1 doctor, 3 tiers, doctorVisitDuration = 10, boringDuration = 4
    // Patients can't be seen before boredom occurs
    DES sim(0, 1, 3, 0, 10, 4, 2, urgency_levels, patient_arrival_times);

    sim.run();
    return 0;
}
