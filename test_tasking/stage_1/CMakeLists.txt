cmake_minimum_required(VERSION 3.25)
project(security_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(security_code
        stage_1.cpp
        )
