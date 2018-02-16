cmake_minimum_required(VERSION 3.2)
project(Aronda)

include_directories(3rd_party/catch2)
include_directories(3rd_party/range)

set(AR_ETL_PATH "" CACHE PATH "Path for ETL header files.")
if(AR_ETL_PATH)
	include_directories(${AR_ETL_PATH})
endif()

set(AR_ETL_PATH "" CACHE PATH "Path for ETL header files.")
if(AR_ETL_PATH)
	include_directories(${AR_ETL_PATH})
endif()

add_subdirectory(lib)
add_subdirectory(unit_tests)
add_subdirectory(gui)
