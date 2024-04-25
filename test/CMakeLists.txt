enable_testing()

find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(mirage_math_tests ${SOURCES})
target_link_libraries(mirage_math_tests
    PRIVATE
    mirage_math
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mirage_math_tests)
