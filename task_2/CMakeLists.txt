cmake_minimum_required(VERSION 3.0)
project(task_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/2017_420_borodin.cpp
        src/header/assign.h
        src/source/assign.cpp
        src/header/state_mapping.h
        src/header/state.h
        src/source/state.cpp
        src/header/args.h
        src/source/args.cpp src/header/run.h src/source/run.cpp)

add_executable(task_2 ${SOURCE_FILES})
