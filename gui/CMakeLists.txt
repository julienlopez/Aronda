include_directories(".")

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(Aronda ${SOURCE_FILES})

target_link_libraries(Aronda libAronda)
