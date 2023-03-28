#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool recurse(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, const size_t pos, vector<size_t>& filled, vector<bool> occupied
) 
{
    if ((pos / sched.size()) >= sched[0].size()) {
        return true;
    }


    size_t row = pos / sched[0].size();
    size_t col = pos % sched[0].size();

    if (col == 0) {
        occupied.clear();
        vector<bool> temp (avail[0].size());
        occupied = temp;
    }

    for (size_t i = 0; i < avail[row].size(); i++) {
        if (avail[row][i] == 1 && filled[i] < maxShifts && !occupied[i]) {
            sched[row][col] = i;
            filled[i]++;
            occupied[i] = true;
            if (recurse(avail, dailyNeed, maxShifts, sched, pos+1, filled, occupied)) {
                return true;
            } else {
                filled[i]--;
                sched[row][col] = 0;
                occupied[i] = false;
            }
        }
    }

    return false;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    for (size_t i = 0; i < avail.size(); i++) {
        vector<Worker_T> vec;
        for (size_t j = 0; j < dailyNeed; j++) {
            vec.push_back(0);
        }
        sched.push_back(vec);
    }

    vector<size_t> filled (avail[0].size());
    vector<bool> occupied (avail[0].size());

    return recurse(avail, dailyNeed, maxShifts, sched, 0, filled, occupied);
}

