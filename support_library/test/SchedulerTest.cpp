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

#include <gtest/gtest.h>

#include "../src/Scheduler.h"
#include "../src/Callback.h"

class TestTask {
public:
    static void callback(void* self) {
        static_cast<TestTask*>(self)->calls++;
    }

    int calls{0};
};

TEST(TaskTest, Callback) {
    TestTask task{};
    Callback scheduler_task{TestTask::callback, &task};
    scheduler_task();
    ASSERT_EQ(task.calls, 1);
}

TEST(TaskTest, DefaultConstructionTest) {
    Callback scheduler_task{};
    EXPECT_NO_THROW(scheduler_task());
}

TEST(SchedulerTest, Construction) {
    Scheduler scheduler{};
}


TEST(SchedulerTest, AddPeriodicTaskTest) {
    TestTask task{};

    Scheduler scheduler{};
    EXPECT_EQ(0, scheduler.addPeriodicTask(Callback{TestTask::callback, &task}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(Callback{TestTask::callback, &task}, 100));
}

TEST(SchedulerTest, TickTest) {
    TestTask task1{};
    TestTask task2{};

    Scheduler scheduler{};
    EXPECT_EQ(0, scheduler.addPeriodicTask(Callback{TestTask::callback, &task1}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(Callback{TestTask::callback, &task2}, 120));

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
    EXPECT_EQ(0, scheduler.addPeriodicTask(Callback{TestTask::callback, &task1}, 100));
    EXPECT_EQ(1, scheduler.addPeriodicTask(Callback{TestTask::callback, &task2}, 120));
    EXPECT_EQ(2, scheduler.addPeriodicTask(Callback{TestTask::callback, &task3}, 130));

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