file(GLOB_RECURSE SOURCES *.cpp)
add_executable(mirage_math_tests ${SOURCES})
target_link_libraries(mirage_math_tests
    PRIVATE
    mirage_math
    gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(mirage_math_tests)
