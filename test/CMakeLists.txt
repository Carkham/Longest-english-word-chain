cmake_minimum_required(VERSION 3.0.2)

enable_testing()
file(GLOB core_files ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB lib_files
        ${PROJECT_SOURCE_DIR}/src/ArgParser.cpp
        ${PROJECT_SOURCE_DIR}/src/IOUtil.cpp
        )
add_executable(
        unit_tests
        Core_test.cpp
        ArgParser_test.cpp
        IOUtil_test.cpp
        ${core_files}
        ${lib_files}
)

target_link_libraries(unit_tests
        GTest::gtest_main
        )

include(GoogleTest)
gtest_discover_tests(unit_tests
        PROPERTIES
        LABELS "unit"
        DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
        )