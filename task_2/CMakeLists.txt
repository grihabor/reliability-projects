cmake_minimum_required(VERSION 3.0)
project(task_2)

set(CMAKE_CXX_STANDARD 11)

file(
        GLOB SOURCE_FILES
        src/2017_420_borodin.cpp
        "src/header/init/*.h"
        "src/source/init/*.cpp"
        "src/header/*.h"
        "src/source/*.cpp"
)

add_executable(task_2 ${SOURCE_FILES} src/header/typedefs.h)
