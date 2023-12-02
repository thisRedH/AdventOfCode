cmake_minimum_required(VERSION 3.21.0)

project(AoC23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_FILES "./*.c" "./*.cc" "./*.cpp" "./*.cxx")
set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE CXX)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE INPUT_FILE "./input/*")
foreach(FILE ${INPUT_FILE})
    get_filename_component(BARENAME ${FILE} NAME)
    configure_file(${FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/input/${BARENAME} COPYONLY)
endforeach()
