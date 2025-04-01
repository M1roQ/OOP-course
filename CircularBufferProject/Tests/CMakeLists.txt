cmake_minimum_required(VERSION 3.22)

project(test LANGUAGES CXX)

add_executable(testapp CBTests.cpp)
target_link_libraries(testapp PRIVATE gtest pthread)
target_link_libraries(testapp PUBLIC CircularBuffer)
enable_testing()
include(GoogleTest)
gtest_discover_tests(testapp)