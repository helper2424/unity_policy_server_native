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

set(LIB_TYPE SHARED)

set( SOURCES )
set( HEADERS )

set(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/CMake
)

message(STATUS "Building project with build type ${CMAKE_BUILD_TYPE}")

set(KNOWN_BUILD_TYPES Debug Performance_Debug Release_Debug)
is_known("${CMAKE_BUILD_TYPE}" "${KNOWN_BUILD_TYPES}" IS_KNOWN)
if (NOT IS_KNOWN)
	message(FATAL_ERROR "Unknown build type ${CMAKE_BUILD_TYPE}, known types are ${KNOWN_BUILD_TYPES}")
endif (NOT IS_KNOWN)

set(DEBUG_BUILD_TYPES Debug Performance_Debug)
is_debug("${CMAKE_BUILD_TYPE}" "${DEBUG_BUILD_TYPES}" IS_DEBUG)
message(STATUS "Debug flag is set to ${IS_DEBUG}")

if (IS_DEBUG)
	add_definitions(-DDEBUG)
	set(SERVER_BASE_BUILD_COMPONENT "Debug")
	set(IS_TEST 1)
else(IS_DEBUG)
	set(SERVER_BASE_BUILD_COMPONENT "Release")
	set(IS_TEST 0)
endif(IS_DEBUG)

if (IS_TEST)
	find_package(GTest)
	if (GTest_FOUND)
		add_definitions(-DTEST)
	else(GTest_FOUND)
		message(WARNING "Unit testing library GTest is not found, tests will not be built")
	endif(GTest_FOUND)
endif(IS_TEST)

find_package(TBB REQUIRED)
find_package(Threads REQUIRED)
find_package(ServerBase ${SERVERBASE_VERSION} REQUIRED COMPONENTS ${SERVER_BASE_BUILD_COMPONENT})

set(CMAKE_C_COMPILER "${CXX_COMPILER_${CMAKE_BUILD_TYPE}}")
set(CMAKE_CXX_COMPILER "${CXX_COMPILER_${CMAKE_BUILD_TYPE}}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_STANDARD_VERSION}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O${CXX_OPTIMIZATION_LEVEL_${CMAKE_BUILD_TYPE}}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_ADDITIONAL_OPTIONS_${CMAKE_BUILD_TYPE}}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_ADDITIONAL_COMPILE_OPTIONS}")

add_definitions(${CXX_DEFINES})

include_directories(SYSTEM ${TBB_INCLUDE_DIR})

set (LINK_LIBRARIES
	"${ServerBase_LIBRARIES}"
	"${TBB_LIBRARIES}"
	"${MySQLpp_LIBRARIES}"
	"${CMAKE_THREAD_LIBS_INIT}"
	"${CppUnit_LIBRARIES}"
	"${GTest_LIBRARIES}"
)

add_subdirectory(source)

if(Boost_FOUND AND Libev_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(policy_server main.cpp) 
    target_link_libraries(policy_server ${Boost_LIBRARIES})
    target_link_libraries(policy_server ${Libev_LIBRARIES})
endif()