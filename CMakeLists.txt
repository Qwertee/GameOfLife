cmake_minimum_required(VERSION 3.7)
project(GameOfLife)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/life.h src/life.cpp)
add_executable(GameOfLife ${SOURCE_FILES})
target_link_libraries(GameOfLife ${CURSES_LIBRARIES})