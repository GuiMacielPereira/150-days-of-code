cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the output directory for executables
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

# Set the default build system to Ninja if available
if (UNIX AND NOT APPLE)
    execute_process(COMMAND which ninja OUTPUT_VARIABLE NINJA_PATH)
    if (NINJA_PATH)
        message(STATUS "Using Ninja as the default generator")
        set(CMAKE_GENERATOR "Ninja" CACHE STRING "Default generator" FORCE)
    endif()
endif()

# Find all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Iterate over each .cpp file and generate an executable
foreach(SOURCE_FILE IN LISTS SOURCES)
    # Extract the file name without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    # Generate executable
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    # Add directory for extra header files
    target_include_directories(${EXECUTABLE_NAME} PRIVATE "~/Applications/C-Turtle")
endforeach()
