project(synthetic)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
include_directories("include/")
add_subdirectory("src/")
add_executable(synthetic src/main.cpp)
target_link_libraries(synthetic GRAPH)