cmake_minimum_required (VERSION 2.6)

project(Unity_policy_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS program_options) 

set(CXX_OPTIMIZATION_LEVEL_Debug 0)
set(CXX_OPTIMIZATION_LEVEL_Performance_Debug 0)
set(CXX_OPTIMIZATION_LEVEL_Release_Debug fast)

set(CXX_ADDITIONAL_COMPILE_OPTIONS "-pedantic -pedantic-errors -Werror -Wextra -Wdeprecated -Wall -pipe -march=native -Wno-missing-braces -Wno-inconsistent-missing-override -g")
set(CXX_DEFINES -DEV_COMPAT3=0 -D__STDC_FORMAT_MACROS)
set(EXECUTABLE_NAME unity_policy_server)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(LIB_TYPE SHARED)

set( SOURCES )
set( HEADERS )

set(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
)

find_package(TBB REQUIRED)
find_package(Threads REQUIRED)
find_package(LIBEV REQUIRED)

set(CMAKE_C_COMPILER "${CXX_COMPILER_${CMAKE_BUILD_TYPE}}")
set(CMAKE_CXX_COMPILER "${CXX_COMPILER_${CMAKE_BUILD_TYPE}}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_ADDITIONAL_COMPILE_OPTIONS}")

add_definitions(${CXX_DEFINES})

include_directories(SYSTEM ${TBB_INCLUDE_DIR})

if(Boost_FOUND AND LIBEV_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()

add_subdirectory(src)