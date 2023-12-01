cmake_minimum_required(VERSION 3.21.0)

project(AoC23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

file(GLOB_RECURSE SRC_FILES "./*.c" "./*.cc" "./*.cpp" "./*.cxx")
set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE CXX)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
