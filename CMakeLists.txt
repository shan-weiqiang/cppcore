cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


set(TARGET_NAME switch_type)

add_executable(${TARGET_NAME} ./test/test.cpp)
target_include_directories(
    ${TARGET_NAME} PUBLIC
    ./include
)

enable_testing()
target_link_libraries(
    ${TARGET_NAME} PUBLIC
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})

