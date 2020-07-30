cmake_minimum_required(VERSION 2.8)

project(MemoryPool)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

#find_package(GTest REQUIRED)

#include_directories(${GTEST_INCLUDE_DIRS})

include_directories(
	./
)

add_executable(tests 
	test/test.cpp
)

#target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(tests tests)