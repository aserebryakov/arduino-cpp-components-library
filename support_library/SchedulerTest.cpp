#include <gtest/gtest.h>

#include "Scheduler.h"
#include "SchedulerTask.h"

class TestTask {
public:
    static void callback(void* self) {
        static_cast<TestTask*>(self)->calls++;
    }

    int calls{0};
};

TEST(TaskTest, Callback) {
    TestTask task{};
    SchedulerTask scheduler_task{TestTask::callback, &task};
    scheduler_task();
    ASSERT_EQ(task.calls, 1);
}

TEST(SchedulerTest, Construction) {
    Scheduler scheduler{};
}


TEST(SchedulerTest, AddPeriodicTaskTest) {
    Scheduler scheduler{};
    TestTask task{};
    SchedulerTask{TestTask::callback, &task};

    EXPECT_EQ(0, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task}, 100));
}