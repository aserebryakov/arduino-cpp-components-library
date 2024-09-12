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
    TestTask task{};

    Scheduler scheduler{};
    EXPECT_EQ(0, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task}, 100));
}

TEST(SchedulerTest, TickTest) {
    TestTask task1{};
    TestTask task2{};

    Scheduler scheduler{};
    EXPECT_EQ(0, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task1}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task2}, 120));

    scheduler.tick(110);
    EXPECT_EQ(task1.calls, 1);
    EXPECT_EQ(task2.calls, 0);

    scheduler.tick(20);
    EXPECT_EQ(task1.calls, 1);
    EXPECT_EQ(task2.calls, 1);
}