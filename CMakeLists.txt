cmake_minimum_required(VERSION 3.16)
project(FUNC_FACTORY)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  funcTest
  lib/test/funcTest.cpp
)
target_link_libraries(
  funcTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(funcTest)