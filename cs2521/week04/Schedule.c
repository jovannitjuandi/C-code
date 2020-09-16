// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule {
    Tree times;
    int  count;
};

// Creates a new schedule
Schedule ScheduleNew(void) {
    Schedule s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s) {
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int  ScheduleCount(Schedule s) {
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
bool ScheduleAdd(Schedule s, Time t) {
    // TODO: Modify the following code
    
    Time before = TreeFloor(s->times, t);
    Time after = TreeCeiling(s->times, t);
    
    if (s->count == 0) {
        TreeInsert(s->times, t);
        s->count++;
        return true;
    } else {
        // no before time
        if (before == NULL) {
            // check it's not between 10 minutes before the next flight
            if (TimeCmp(t, TimeSubtractMinutes(after, 10)) < 0) {
                TreeInsert(s->times, t);
                s->count++;
                return true;
            }
            
            // check it's not between 10 minutes after the next flight
            else if (TimeCmp(TimeAddMinutes(after, 10), t) < 0){
                TreeInsert(s->times, t);
                s->count++;
                return true;
            }
            
            // if it's within 10 minutes before or after then don't add
            else {
                return false;
            }
        } else if (after == NULL) {
            // check it's not between 10 minutes before the prev flight
            if (TimeCmp(t, TimeSubtractMinutes(before, 10)) < 0) {
                TreeInsert(s->times, t);
                s->count++;
                return true;
            }
            
            // check it's not between 10 minutes after the prev flight
            else if (TimeCmp(TimeAddMinutes(before, 10), t) < 0){
                TreeInsert(s->times, t);
                s->count++;
                return true;
            }
            
            // if it's within 10 minutes before or after then don't add
            else {
                return false;
            }
        } else {
            // check it's not between 10 minutes before or after next or prev flights
            if ((TimeCmp(TimeAddMinutes(after, 10), t) >= 0) & (TimeCmp(t, TimeSubtractMinutes(after, 10)) >= 0)) {
               return false;
            } else if ((TimeCmp(TimeAddMinutes(before, 10), t) >= 0) & (TimeCmp(t, TimeSubtractMinutes(before, 10)) >= 0)) {
                return false;
            } else {
                TreeInsert(s->times, t);
                s->count++;
                return true;
            }
        }
    }
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode) {
    if (mode == 1) {
        TreeList(s->times);
    } else if (mode == 2) {
        TreeShow(s->times);
    }
}
