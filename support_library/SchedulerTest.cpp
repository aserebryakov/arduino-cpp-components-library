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

TEST(TaskTest, DefaultConstructionTest) {
    SchedulerTask scheduler_task{};
    EXPECT_NO_THROW(scheduler_task());
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

    scheduler.tick(10);
    EXPECT_EQ(task1.calls, 1);
    EXPECT_EQ(task2.calls, 1);
}

TEST(SchedulerTest, RemoveTaskTest) {
    TestTask task1{};
    TestTask task2{};
    TestTask task3{};

    Scheduler scheduler{};
    EXPECT_EQ(0, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task1}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task2}, 120));
    EXPECT_EQ(2, scheduler.addPeriodicTask(SchedulerTask{TestTask::callback, &task3}, 130));

    scheduler.tick(110);
    EXPECT_EQ(task1.calls, 1);
    EXPECT_EQ(task2.calls, 0);
    EXPECT_EQ(task3.calls, 0);

    EXPECT_TRUE(scheduler.removeTask(1));

    scheduler.tick(40);
    EXPECT_EQ(task1.calls, 1);
    EXPECT_EQ(task2.calls, 0);
    EXPECT_EQ(task3.calls, 1);
}