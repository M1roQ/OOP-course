#include <gtest/gtest.h>
#include "../mytime.h"
#include <sstream>
#include <vector>
#include <memory>

TEST(TimeConstructorTest, DefaultConstructor) {
    Time t;
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 0);
    EXPECT_EQ(t.GetSeconds(), 0);
}

TEST(TimeConstructorTest, ParameterizedConstructor) {
    Time t(1, 30, 45);
    EXPECT_EQ(t.GetHours(), 1);
    EXPECT_EQ(t.GetMinutes(), 30);
    EXPECT_EQ(t.GetSeconds(), 45);
}

TEST(TimeOperatorTest, PlusEqualOperator) {
    Time t(1, 30, 45);
    t += 3600; // +1h
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 30);
    EXPECT_EQ(t.GetSeconds(), 45);
}

TEST(TimeOperatorTest, EqualityOperator) {
    Time t1(1, 30, 45);
    Time t2(1, 30, 45);
    EXPECT_TRUE(t1 == t2);
}

TEST(TimeAccessorsTest, ToSeconds) {
    Time t(2, 30, 15);
    EXPECT_EQ(t.ToSeconds(), 9015);
}

TEST(TimeAssignmentTest, MinusEqualOperator_Correct) {
    Time t(2, 0, 0);
    t -= 3661; // -1 h, 1 s
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 58);
    EXPECT_EQ(t.GetSeconds(), 59);
}

TEST(TimeIOTest, OutputOperator) {
    Time t(1, 30, 45);
    std::ostringstream oss;
    oss << t;
    EXPECT_EQ(oss.str(), "1:30:45");
}

TEST(TimeIOTest, InputOperator) {
    Time t;
    std::istringstream iss("2:45:30");
    iss >> t;
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 45);
    EXPECT_EQ(t.GetSeconds(), 30);
}

TEST(TimeDynamicMemoryTest, CreateSingleObject) {
    Time* t = new Time(10, 20, 30);
    EXPECT_EQ(t->GetHours(), 10);
    EXPECT_EQ(t->GetMinutes(), 20);
    EXPECT_EQ(t->GetSeconds(), 30);
    delete t;
}

TEST(TimeDynamicMemoryTest, CreateArrayOfObjects) {
    Time* times = new Time[3] {
        Time(1, 0, 0),
        Time(2, 30, 0),
        Time(5, 45, 10)
    };
    
    EXPECT_EQ(times[0].GetHours(), 1);
    EXPECT_EQ(times[1].GetMinutes(), 30);
    EXPECT_EQ(times[2].GetSeconds(), 10);
    
    delete[] times;
}

TEST(TimeContainerTest, VectorOfTimeObjects) {
    std::vector<Time> timeVec;
    timeVec.push_back(Time(1, 30, 45));
    timeVec.push_back(Time(2, 30, 45));

    EXPECT_EQ(timeVec[0].GetHours(), 1);
    EXPECT_EQ(timeVec[1].GetMinutes(), 30);
    EXPECT_EQ(timeVec[1].GetSeconds(), 45);
}

TEST(TimeSmartPointerTest, UniquePointer) {
    std::unique_ptr<Time> t = std::make_unique<Time>(10, 20, 30);
    EXPECT_EQ(t->GetHours(), 10);
    EXPECT_EQ(t->GetMinutes(), 20);
    EXPECT_EQ(t->GetSeconds(), 30);
}

TEST(TimeSmartPointerTest, SharedPointer) {
    std::shared_ptr<Time> t1 = std::make_shared<Time>(1, 2, 3);
    std::shared_ptr<Time> t2 = t1;  
    EXPECT_EQ(t1->GetHours(), 1);
    EXPECT_EQ(t2->GetMinutes(), 2);
}


TEST(TimeNegativeTest, MinusEqualOperator_LargeSubtraction) {
    Time t(0, 0, 30);
    t -= 90; 
    EXPECT_EQ(t.GetHours(), 23); 
    EXPECT_EQ(t.GetMinutes(), 59);
    EXPECT_EQ(t.GetSeconds(), 0);
}
