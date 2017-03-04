cmake_minimum_required(VERSION 2.8)

project(labyrinth)

include_directories("include")
file(GLOB SOURCES "src/*.c" "include/*.h")

add_executable(labyrinth ${SOURCES})
