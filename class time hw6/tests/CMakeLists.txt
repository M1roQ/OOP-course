# Устанавливаем GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Создаём тестовый target
add_executable(TimeTests test_time.cpp)

# Линкуем GoogleTest и библиотеку TimeLib
target_link_libraries(TimeTests
    PRIVATE
        GTest::gtest_main
        TimeLib
)

# Включаем GoogleTest
include(GoogleTest)
gtest_discover_tests(TimeTests)
