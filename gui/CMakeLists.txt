include_directories(".")
include_directories("../lib")

set(AR_QT_ROOT_DIR "" CACHE PATH "Use specific Qt folder?")
set(AR_QT_MODULES Qt5Core Qt5Gui Qt5Widgets)

if( NOT "${AR_QT_ROOT_DIR}" STREQUAL "")
	link_directories(${AR_QT_ROOT_DIR}/lib)
	foreach(MODULE ${AR_QT_MODULES})
		include(${AR_QT_ROOT_DIR}/lib/cmake/${MODULE}/${MODULE}Config.cmake)
		include_directories(${${MODULE}_INCLUDE_DIRS})
	endforeach()
else()
	foreach(MODULE ${AR_QT_MODULES})
		find_package(${MODULE} REQUIRED)
		include_directories(${${MODULE}_INCLUDE_DIRS})
	endforeach()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(Aronda ${SOURCE_FILES} images.qrc)

target_link_libraries(Aronda libAronda)
foreach(MODULE ${AR_QT_MODULES})
	target_link_libraries(Aronda ${${MODULE}_LIBRARIES})
endforeach()
