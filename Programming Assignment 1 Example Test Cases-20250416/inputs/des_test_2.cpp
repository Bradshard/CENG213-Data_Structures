#include <iostream>
#include "DES.h"

int main() {
    int arrival_times[1] = {1};
    int urgency_levels[1] = {0};

    DES sim(1, 1, 1, 2, 3, 10, 1, urgency_levels, arrival_times);
    sim.run();

    return 0;
}
