cmake_minimum_required(VERSION 3.15)
project(AVLTree)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(AVLTree src/main.cpp)


add_subdirectory(lib/googletest)
add_executable(run_tests 
    tests/test_tree_node.cpp
    tests/test_binary_tree.cpp)
target_link_libraries(run_tests 
    PRIVATE 
    gtest_main 
    gtest 
    pthread
)

target_include_directories(run_tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(run_tests)

enable_testing()
add_test(NAME UnitTests COMMAND run_tests)