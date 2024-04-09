enable_testing()

set(SOURCES 
  vec3.test.cpp)
add_executable(mirage-math-tests ${SOURCES})

target_link_libraries(mirage-math-tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mirage-math-tests)
