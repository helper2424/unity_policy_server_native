cmake_minimum_required (VERSION 2.6)

project(Unity_policy_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
aux_source_directory(.)
add_executable(policy_server main.cpp)
