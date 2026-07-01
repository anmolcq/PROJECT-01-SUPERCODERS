cmake_minimum_required(VERSION 3.16)

project(RedisLiteProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

# Header files
include_directories(include)


set(REDIS_SOURCES
    src/CLI.cpp
    src/CommandParser.cpp
    src/RedisLite.cpp
)



file(GLOB DYNAMICARRAY_TESTS
    tests/DynamicArray/*.cpp
)

add_executable(DynamicArrayTests
    ${DYNAMICARRAY_TESTS}
)

target_link_libraries(DynamicArrayTests
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(DynamicArrayTests)


file(GLOB LINKEDLIST_TESTS
    tests/LinkedList/*.cpp
)

add_executable(LinkedListTests
    ${LINKEDLIST_TESTS}
)

target_link_libraries(LinkedListTests
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(LinkedListTests)



file(GLOB HASHMAP_TESTS
    tests/Hashmap/*.cpp
)

add_executable(HashMapTests
    ${HASHMAP_TESTS}
)

target_link_libraries(HashMapTests
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(HashMapTests)



file(GLOB REDIS_TESTS
    tests/RedisLite/*.cpp
)

add_executable(RedisLiteTests
    ${REDIS_TESTS}
    ${REDIS_SOURCES}
)

target_link_libraries(RedisLiteTests
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(RedisLiteTests)