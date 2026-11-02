cmake_minimum_required(VERSION 3.16)

project(Bad_Apple VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)

add_subdirectory(src)

add_executable(Bad_Apple main.cxx)

target_link_libraries(Bad_Apple PRIVATE 
    src_library 
    SDL3::SDL3
)
