cmake_minimum_required(VERSION 3.2)
project(Aronda)

set(CMAKE_CXX_STANDARD 14)

include_directories(3rd_party/catch2)
include_directories(3rd_party/range)
include_directories(expected)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	message("using visual")
	add_compile_options("/std:c++latest")
	add_definitions("-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE")
else()
	message("using ${CMAKE_CXX_COMPILER_ID}")
	add_definitions("-std=c++17")
	add_definitions("-fprofile-arcs")
	add_definitions("-ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
endif()

set(AR_ETL_PATH "" CACHE PATH "Path for ETL header files.")
if(AR_ETL_PATH)
	include_directories(${AR_ETL_PATH})
endif()

set(AR_GSL_PATH "" CACHE PATH "Path for GSL header files.")
if(AR_GSL_PATH)
	include_directories(${AR_GSL_PATH})
endif()

set(AR_BOOST_PATH "" CACHE PATH "Path for boost directory.")
if(AR_BOOST_PATH)
	include_directories(${AR_BOOST_PATH})
endif()

add_subdirectory(lib)
add_subdirectory(unit_tests)
add_subdirectory(gui)
