find_package(GTest CONFIG REQUIRED)

add_executable(dama_tests
  test.cpp
  test_engine.cpp
  legal_move.cpp
)
target_link_libraries(dama_tests PRIVATE dama::engine dama_warnings GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(dama_tests)