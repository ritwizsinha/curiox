# Minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Project name and version
project(curiox VERSION 1.0 LANGUAGES C CXX)

# Set the PostgreSQL include and library paths
find_path(POSTGRES_INCLUDE_DIR NAMES postgres.h HINTS /usr/include/postgresql/16/server)


if(NOT POSTGRES_INCLUDE_DIR)
    message(FATAL_ERROR "PostgreSQL development files not found. Please install them.")
endif()

# Set the source directory
set(SRC_DIR src)

# Gather all source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c" "${SRC_DIR}/*.cpp")

# Set the library output name
set(LIBRARY_OUTPUT_NAME curiox)

# Add the library
add_library(${LIBRARY_OUTPUT_NAME} SHARED ${SOURCES})

# Include PostgreSQL headers
target_include_directories(${LIBRARY_OUTPUT_NAME} PUBLIC
    ${POSTGRES_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include)


# Set the output directory for the shared library
set_target_properties(${LIBRARY_OUTPUT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PREFIX "" # Removes the "lib" prefix from the library name
    SUFFIX ".so" # Sets the shared library extension
)

# Set the C and C++ standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
