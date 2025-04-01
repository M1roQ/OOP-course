cmake_minimum_required(VERSION 3.11)

# Название проекта
project(TimeProject VERSION 1.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаём библиотеку для общего кода
add_library(TimeLib STATIC mytime.cpp)
target_include_directories(TimeLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Основное приложение
add_executable(TimeProject main.cpp)
target_link_libraries(TimeProject PRIVATE TimeLib)

# Опция для включения тестов
option(ENABLE_TESTS "Enable building tests" ON)

# Включаем тесты, если ENABLE_TESTS=ON
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
