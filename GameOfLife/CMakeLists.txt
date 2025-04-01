cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Game-Of-Life VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


enable_testing()
add_subdirectory(lib)

target_include_directories(GameOfLife PUBLIC .) # PRIVATE

add_executable(game main.cpp)

target_link_libraries(game GameOfLife) # PRIVATE

add_subdirectory(tests)