// MIT License
//
// Copyright (c) 2024 Alexander Serebryakov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Scheduler.h"

SchedulerTaskId Scheduler::addPeriodicTask(SchedulerTask&& task, const SchedulerTaskPeriod period) {
    periodic_tasks[next_task_slot] = PeriodicTask{task, period};
    const auto taskId{next_task_slot};
    next_task_slot++;
    total_tasks++;
    return taskId;
}

void Scheduler::tick(const IntervalMs interval_ms) {
    for (SchedulerTaskId task_id = 0; task_id < total_tasks; task_id++) {
        periodic_tasks[task_id].tick(interval_ms);
    }
}

Scheduler::PeriodicTask::PeriodicTask(const SchedulerTask& task, const SchedulerTaskPeriod period) : task{task},
    period{period}, interval_till_next_call{period} {
}

void Scheduler::PeriodicTask::tick(const IntervalMs interval_ms) {
    interval_till_next_call -= interval_ms;

    if (interval_till_next_call > 0) {
        return;
    }

    task();
    reset();
}

void Scheduler::PeriodicTask::reset() {
    interval_till_next_call = period;
}
