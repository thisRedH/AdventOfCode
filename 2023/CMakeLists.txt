cmake_minimum_required(VERSION 3.21.0)

project(AoC23)

# Compiler Options Global
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options(
#TODO:    -Wall -Werror -Wno-error=maybe-uninitialized
    $<$<CONFIG:RELEASE>:-Ofast>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-ggdb3>
)
add_compile_definitions($<$<CONFIG:RELEASE>:NDEBUG>)

# Add executable
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.cc"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.cxx"
)
set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE CXX)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Compiler Options for ${PROJECT_NAME}
MATH(EXPR stack_size "8 * 1024 * 1024") # 8 Mb
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -Wl,--stack,${stack_size})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Libs
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()

# Export input files
file(GLOB_RECURSE INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/input/*")
foreach(FILE ${INPUT_FILE})
    get_filename_component(BARENAME ${FILE} NAME)
    message(STATUS "Copying \"input/${BARENAME}\" to \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/input/${BARENAME}\"")
    configure_file(${FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/input/${BARENAME} COPYONLY)
endforeach()
