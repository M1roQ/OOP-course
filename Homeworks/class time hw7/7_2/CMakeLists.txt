cmake_minimum_required(VERSION 3.11)

# Название проекта
project(TimeProject7_2 VERSION 1.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаём библиотеку для общего кода
add_library(TimeLib7_2 STATIC mytime7_2.cpp)
target_include_directories(TimeLib7_2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Основное приложение
add_executable(TimeProject7_2 main7_2.cpp)
target_link_libraries(TimeProject7_2 PRIVATE TimeLib7_2)

# Опция для включения тестов
# option(ENABLE_TESTS "Enable building tests" ON)

# Включаем тесты, если ENABLE_TESTS=ON
# if(ENABLE_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()
