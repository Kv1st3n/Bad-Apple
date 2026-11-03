cmake_minimum_required(VERSION 3.16)

project(Bad_Apple VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(AVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(AVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(AVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(SWSCALE REQUIRED IMPORTED_TARGET libswscale)

add_subdirectory(src)

add_executable(Bad_Apple main.cxx)

target_link_libraries(Bad_Apple PRIVATE 
    src_library 
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    PkgConfig::AVCODEC
    PkgConfig::AVFORMAT
    PkgConfig::AVUTIL
    PkgConfig::SWSCALE
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/bad-apple-audio.mp3 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/BadApple.mp4
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})