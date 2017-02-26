cmake_minimum_required(VERSION 2.8)

project(labyrinth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

include_directories("include")
file(GLOB SOURCES "src/*.cpp" "include/*.hpp")

add_executable(labyrinth ${SOURCES})
