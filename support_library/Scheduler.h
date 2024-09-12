#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdint>
#include "SchedulerTask.h"

using SchedulerTaskId = uint8_t;
using SchedulerTaskPeriod = uint32_t;

class Scheduler {
public:
    SchedulerTaskId addPeriodicTask(SchedulerTask&& task, SchedulerTaskPeriod period);

private:
    uint8_t nextTaskSlot{0};

};

#endif //SCHEDULER_H
