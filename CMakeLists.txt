cmake_minimum_required (VERSION 2.6)

project(Unity_policy_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(EXECUTABLE_NAME unity_policy_server)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors -Wextra -Wdeprecated -Wall -Wno-unused-parameter -pipe -march=native -Wno-missing-braces -g -O2")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Boost 1.45.0 COMPONENTS program_options)
find_package(TBB REQUIRED)
find_package(Threads REQUIRED)
find_package(LIBEV REQUIRED)

add_definitions(-DEV_COMPAT3=0 -D__STDC_FORMAT_MACROS)

if(NOT Boost_FOUND)
	message(FATAL_ERROR "Undefined Boost program_options library")
endif()

if(NOT TBB_FOUND)
        message(FATAL_ERROR "Undefined tbb library")
endif()

if(NOT LIBEV_FOUND)
	message(FATAL_ERROR "Undefined libev library")
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LIBEV_INCLUDE_DIR})
include_directories(SYSTEM ${TBB_INCLUDE_DIR})

add_subdirectory(src)