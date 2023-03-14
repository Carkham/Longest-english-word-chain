cmake_minimum_required(VERSION 3.0.2)

enable_testing()
add_executable(hello_test hello_test.cpp)

target_link_libraries(hello_test
        PRIVATE ${LIBRARY_OUTPUT_PATH}/libCore.dll
        GTest::gtest_main
        )

include(GoogleTest)
gtest_discover_tests(hello_test)