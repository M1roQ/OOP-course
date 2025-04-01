#include "gtest/gtest.h"
#include "../Circular_Buffer.h"

// === Базовые тесты ===
// Тест для конструктора по умолчанию
TEST(CircularBufferTest_Constructors, DefaultConstructor) {
    CircularBuffer cb;
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
    EXPECT_EQ(cb.capacity(), 0);
}

// Тест для конструктора с емкостью
TEST(CircularBufferTest_Constructors, ConstructorWithCapacity) {
    CircularBuffer cb(10);
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_TRUE(cb.empty());
}

// Тест для конструктора с емкостью и заполнением
TEST(CircularBufferTest_Constructors, ConstructorWithCapacityAndFill) {
    CircularBuffer cb(5, 42);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_FALSE(cb.empty());
    for (int i = 0; i < cb.size(); ++i) {
        EXPECT_EQ(cb[i], 42);
    }
}

// Тест для оператора []
TEST(CircularBufferTest_Operators, OperatorBracket) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb[0], 10);
    EXPECT_EQ(cb[1], 20);
    EXPECT_EQ(cb[2], 30);
}

// Тест для at()
TEST(CircularBufferTest, At) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb.at(0), 10);
    EXPECT_EQ(cb.at(1), 20);
    EXPECT_EQ(cb.at(2), 30);

    EXPECT_THROW(cb.at(3), std::out_of_range); // Проверка на выход за пределы
}

// Тест для front()
TEST(CircularBufferTest, Front) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb.front(), 10);
    EXPECT_NO_THROW(cb.front()); // Проверка, что не бросается исключение

    cb.pop_front();
    EXPECT_EQ(cb.front(), 20);
}

// Тест для back()
TEST(CircularBufferTest, Back) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb.back(), 30);
    EXPECT_NO_THROW(cb.back()); // Проверка, что не бросается исключение

    cb.pop_back();
    EXPECT_EQ(cb.back(), 20);
}

// Тест для push_back()
TEST(CircularBufferTest, PushBack) {
    CircularBuffer cb(5);

    // Заполнение буфера
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);
    cb.push_back(40);
    cb.push_back(50);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_TRUE(cb.full());
  
    // Переполнение буфера
    cb.push_back(60);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb[0], 20); // Проверка перезаписи
    EXPECT_EQ(cb[1], 30);
    EXPECT_EQ(cb[2], 40);
    EXPECT_EQ(cb[3], 50);
    EXPECT_EQ(cb[4], 60);
}

// Тест для push_front()
TEST(CircularBufferTest, PushFront) {
    CircularBuffer cb(5);

    // Заполнение буфера
    cb.push_front(10);
    cb.push_front(20);
    cb.push_front(30);
    cb.push_front(40);
    cb.push_front(50);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_TRUE(cb.full());
 
    // Переполнение буфера
    cb.push_front(60);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb[0], 60); // Проверка перезаписи
    EXPECT_EQ(cb[1], 50);
    EXPECT_EQ(cb[2], 40);
    EXPECT_EQ(cb[3], 30);
    EXPECT_EQ(cb[4], 20);
}

// Тест для pop_back()
TEST(CircularBufferTest, PopBack) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb.size(), 3);
    cb.pop_back();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.back(), 20);

    // Проверка, что pop_back() не выдает исключение для пустого буфера
    EXPECT_NO_THROW(cb.pop_back());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
}

// Тест для pop_front()
TEST(CircularBufferTest, PopFront) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    EXPECT_EQ(cb.size(), 3);
    cb.pop_front();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 20);

    // Проверка, что pop_front() не выдает исключение для пустого буфера
    EXPECT_NO_THROW(cb.pop_front());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 30);
}

// Тест для swap()
TEST(CircularBufferTest, Swap) {
    CircularBuffer cb1(3);
    cb1.push_back(10);
    cb1.push_back(20);

    CircularBuffer cb2(5);
    cb2.push_back(30);
    cb2.push_back(40);
    cb2.push_back(50);

    cb1.swap(cb2);
    EXPECT_EQ(cb1.size(), 3);
    EXPECT_EQ(cb1.capacity(), 5);
    EXPECT_EQ(cb1[0], 30);
    EXPECT_EQ(cb1[1], 40);
    EXPECT_EQ(cb1[2], 50);

    EXPECT_EQ(cb2.size(), 2);
    EXPECT_EQ(cb2.capacity(), 3);
    EXPECT_EQ(cb2[0], 10);
    EXPECT_EQ(cb2[1], 20);
}

// Тест для clear()
TEST(CircularBufferTest, Clear) {
    CircularBuffer cb(5);
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);

    cb.clear();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
    EXPECT_EQ(cb.capacity(), 5);
}

// Тест для set_capacity()
TEST(CircularBufferTest, SetCapacity) {
    CircularBuffer cb(3);
    cb.push_back(10);
    cb.push_back(20);

    // Увеличение емкости
    cb.set_capacity(5);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 10);
    EXPECT_EQ(cb[1], 20);

    // Уменьшение емкости (должно выбросить исключение)
    EXPECT_THROW(cb.set_capacity(1), std::invalid_argument);
}

// Тест для resize()
TEST(CircularBufferTest, Resize) {
    CircularBuffer cb(3);
    cb.push_back(10);
    cb.push_back(20);

    // Увеличение размера
    cb.resize(5, 99);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb[0], 10);
    EXPECT_EQ(cb[1], 20);
    EXPECT_EQ(cb[2], 99);
    EXPECT_EQ(cb[3], 99);
    EXPECT_EQ(cb[4], 99);

    // Уменьшение размера
    cb.resize(2);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb[0], 10);
    EXPECT_EQ(cb[1], 20);
}

// === Тесты для провальных сценариев ===
TEST(CircularBufferTest_Failures, IncorrectAccess) {
    CircularBuffer cb(5);
    
    EXPECT_THROW(cb.front(), std::out_of_range);
    EXPECT_THROW(cb.back(), std::out_of_range);
    EXPECT_THROW(cb.pop_front(), std::out_of_range);
    EXPECT_THROW(cb.pop_back(), std::out_of_range);
}


TEST(CircularBufferTest_Invalid, NegativeCapacity) {
    EXPECT_THROW(CircularBuffer(-1), std::invalid_argument);
}

TEST(CircularBufferTest_Invalid, OutOfRangeAccess) {
    CircularBuffer cb(5);
    cb.push_back(10);
    EXPECT_THROW(cb.at(1), std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
