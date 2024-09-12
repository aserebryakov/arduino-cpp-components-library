//
// Created by alex on 9/12/24.
//

#include "Scheduler.h"

SchedulerTaskId Scheduler::addPeriodicTask(SchedulerTask&& task, const SchedulerTaskPeriod period) {
    return nextTaskSlot++;
}
